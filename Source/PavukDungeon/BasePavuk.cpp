// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePavuk.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/SceneComponent.h"
#include "Projectile.h"
#include "HealthComponent.h"

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
}

// Called when the game starts or when spawned
void ABasePavuk::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->SetSimulatePhysics(false);
}

// Called every frame
void ABasePavuk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector HoldLocation = GetActorLocation() + GetActorForwardVector() * HoldDistance;

	PhysicsHandle->SetTargetLocationAndRotation(HoldLocation, GetActorRotation());
}

void ABasePavuk::Grab()
{
	FVector StartTraceLocation = GetActorLocation();
	FVector EndTraceLocation = StartTraceLocation + GetActorForwardVector() * GrabDistance;

	FCollisionShape CollisionSphere = FCollisionShape::MakeSphere(GrabSphereRadius);

	WasHit = GetWorld()->SweepSingleByChannel(
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
}

void ABasePavuk::Release()
{
	PhysicsHandle->ReleaseComponent();
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