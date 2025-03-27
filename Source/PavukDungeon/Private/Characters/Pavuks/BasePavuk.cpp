// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Pavuks/BasePavuk.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/HealthComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePavuk::ABasePavuk()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CharacterBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collion1"));
	CharacterBoxCollision->SetCanEverAffectNavigation(false);

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

	CharacterBoxCollision->SetBoxExtent(FVector(60, 32, 32));
	CharacterBoxCollision->AddLocalOffset(FVector(0, 0, 7));
	CharacterBoxCollision->SetupAttachment(RootComponent);
	CharacterBoxCollision->SetCollisionProfileName(TEXT("Pawn"));
	CharacterBoxCollision->CanCharacterStepUpOn = ECB_No;

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawner"));
	ProjectileSpawnPoint->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("SpawnSocket"));

	GetCapsuleComponent()->SetCapsuleSize(25.f, 25.f);
	GetCapsuleComponent()->SetSimulatePhysics(true);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Character Health Component"));

	BoxDamagerTail = CreateDefaultSubobject<UBoxComponent>(TEXT("Damager box tail"));
	BoxDamagerTail->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("DamagerSocket"));

	BoxDamagerJaw = CreateDefaultSubobject<UBoxComponent>(TEXT("Damager box jaw"));
	BoxDamagerJaw->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("JawDamagerSocket"));
}

// Called when the game starts or when spawned
void ABasePavuk::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->SetSimulatePhysics(false);

	MeleeAttacksArray.Add(TailAttack);
	MeleeAttacksArray.Add(JawAttack);

	BoxDamagerTail->OnComponentBeginOverlap.AddDynamic(this, &ABasePavuk::OverlapTailDamagerBegin);
	BoxDamagerJaw->OnComponentBeginOverlap.AddDynamic(this, &ABasePavuk::OverlapJawDamagerBegin);
	
	BoxDamagerJaw->OnComponentEndOverlap.AddDynamic(this, &ABasePavuk::OverlapJawDamagerEnd);
}

void ABasePavuk::Grab()
{
	FVector StartTraceLocation = GetActorLocation();
	FVector EndTraceLocation = StartTraceLocation + GetActorForwardVector() * GrabDistance;

	FCollisionShape CollisionSphere = FCollisionShape::MakeSphere(GrabSphereRadius);

	bool WasHit = GetWorld()->SweepSingleByChannel(
		GrabHitResult, 
		StartTraceLocation, 
		EndTraceLocation, 
		FQuat::Identity, 
		ECC_GameTraceChannel2, 
		CollisionSphere
	);

	if (WasHit)
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			GrabHitResult.GetComponent(), 
			NAME_None, 
			GrabHitResult.ImpactPoint, 
			GrabHitResult.GetComponent()->GetComponentRotation()
		);
	}

	IsHoldingObject = true;

	UpdatePhysicsHandleComponent();
}

void ABasePavuk::Release()
{
	PhysicsHandle->ReleaseComponent();
	IsHoldingObject = false;
}

void ABasePavuk::Shoot()
{
	Super::Shoot();
}

void ABasePavuk::MeleeAttack()
{
	if (MeleeAttacksArray.Num() > 0)
	{
		int32 RandomAttackIndex = FMath::RandRange(0, MeleeAttacksArray.Num() - 1);
		if (MeleeAttacksArray[RandomAttackIndex])
		{
			CurrentAnimMontage = MeleeAttacksArray[RandomAttackIndex];

			FOnMontageEnded MontageEndedDelegate;
			MontageEndedDelegate.BindUObject(this, &ABasePavuk::ClearDamagedActor);

			GetMesh()->GetAnimInstance()->Montage_Play(MeleeAttacksArray[RandomAttackIndex]);
			GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(MontageEndedDelegate, MeleeAttacksArray[RandomAttackIndex]);
		}

		if (HaveToDamageActor && MeleeAttacksArray[RandomAttackIndex])
		{
			DamageActor(HaveToDamageActor);
		}
	}
}

void ABasePavuk::OverlapJawDamagerBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OverlappedComp->GetOwner() != OtherActor && !OtherComp->ComponentHasTag(FName("IgnoreDamage")))
	{
		HaveToDamageActor = OtherActor;
	}
}
void ABasePavuk::OverlapJawDamagerEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (HaveToDamageActor == OtherActor)
	{
		HaveToDamageActor = nullptr;
	}
}

void ABasePavuk::OverlapTailDamagerBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OverlappedComp->GetOwner() != OtherActor && OtherActor != this && DamagedActor != OtherActor && !OtherComp->ComponentHasTag(FName("IgnoreDamage")))
	{	
		DamageActor(OtherActor);
		DamagedActor = OtherActor;
	}
}

void ABasePavuk::UpdatePhysicsHandleComponent()
{
	if (!IsHoldingObject)
	{
		return;
	}
	FVector HoldLocation = GetActorLocation() + GetActorForwardVector() * HoldDistance;
	PhysicsHandle->SetTargetLocationAndRotation(HoldLocation, GetActorRotation());
	
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ABasePavuk::UpdatePhysicsHandleComponent);	
}

void ABasePavuk::ClearDamagedActor(UAnimMontage* Montage, bool bInterrupted)
{
	if (CurrentAnimMontage == Montage)
	{
		DamagedActor = nullptr;
		CurrentAnimMontage = nullptr;
	}
}

void ABasePavuk::DamageActor(AActor* ToDamageActor)
{		
	UGameplayStatics::ApplyDamage(ToDamageActor, MeleeDamage, GetInstigatorController(), this, UDamageType::StaticClass());
	UE_LOG(LogTemp, Warning, TEXT("MeleeDamage to: %s"), *ToDamageActor->GetName());
}