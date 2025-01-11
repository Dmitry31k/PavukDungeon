// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Pavuks/BasePavuk.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/SceneComponent.h"
#include "Actors/EnemyActors/Projectile.h"
#include "Components/HealthComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SpotLightComponent.h"

// Sets default values
ABasePavuk::ABasePavuk()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision1 = CreateDefaultSubobject<USphereComponent>(TEXT("Collion1"));
	SphereCollision2 = CreateDefaultSubobject<USphereComponent>(TEXT("Collion2"));
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

	SphereCollision1->AddLocalOffset(FVector(-40, 0, 7));
	SphereCollision2->AddLocalOffset(FVector(50, 0, 7));
	SphereCollision1->SetupAttachment(RootComponent);
	SphereCollision2->SetupAttachment(RootComponent);
	SphereCollision1->SetCollisionProfileName(TEXT("Pawn"));
	SphereCollision2->SetCollisionProfileName(TEXT("Pawn"));
	SphereCollision1->CanCharacterStepUpOn = ECB_No;
	SphereCollision2->CanCharacterStepUpOn = ECB_No;

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

// Called every frame
void ABasePavuk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void ABasePavuk::Release()
{
	PhysicsHandle->ReleaseComponent();
	IsHoldingObject = false;
}

void ABasePavuk::Shoot()
{
	if (ProjectileClass && CanShoot)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, 
			ProjectileSpawnPoint->GetComponentLocation(), 
			ProjectileSpawnPoint->GetComponentRotation()
		);

		CanShoot = false;
		GetWorldTimerManager().SetTimer(SetShootTimerHandle, this, &ABasePavuk::SetCanShootTrue, RechargingShootSpeed, false);

		Projectile->SetOwner(this);
	}
}

void ABasePavuk::SetCanShootTrue()
{
	CanShoot = true;
}

void ABasePavuk::SetWasMeleeDamageFalse()
{
	WasMeleeDamage = false;
}

void ABasePavuk::MeleeAttack()
{
	if (MeleeAttacksArray.Num() > 0 && !WasMeleeDamage)
	{
		int32 RandomAttackIndex = FMath::RandRange(0, MeleeAttacksArray.Num() - 1);
		if (MeleeAttacksArray[RandomAttackIndex])
		{
			GetMesh()->GetAnimInstance()->Montage_Play(MeleeAttacksArray[RandomAttackIndex]);
		}

		if (HaveToDamageActor && !WasMeleeDamage && MeleeAttacksArray[RandomAttackIndex] != TailAttack)
		{
			UGameplayStatics::ApplyDamage(HaveToDamageActor, MeleeDamage, GetInstigatorController(), this, UDamageType::StaticClass());
		}
	}

	WasMeleeDamage = true;
	GetWorldTimerManager().SetTimer(SetWasMeleeDamagedTimerHandle, this, &ABasePavuk::SetWasMeleeDamageFalse, RechargingMeleeDamageSpeed, false);
}

void ABasePavuk::OverlapJawDamagerBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OverlappedComp->GetOwner() != OtherActor)
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
	if (OverlappedComp->GetOwner() != OtherActor, OtherActor != this)
	{
		if (Cast<USphereComponent>(OtherComp) || Cast<USpotLightComponent>(OtherComp))
		{
			return;
		}
		UGameplayStatics::ApplyDamage(OtherActor, MeleeDamage, GetInstigatorController(), this, UDamageType::StaticClass());
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