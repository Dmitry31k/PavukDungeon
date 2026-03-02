// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EnemyActors/Turret.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Pavuks/PlayerPavuk.h"
#include "Math/UnrealMathUtility.h"
#include "Components/SceneComponent.h"
#include "Actors/EnemyActors/Projectile.h"
#include "Components/OverlapTriggerComponents/TickOptimizer.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	TurretBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	TurretHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawner"));

	TurretBase->SetupAttachment(RootComponent);
	TurretHead->SetupAttachment(TurretBase);
	ProjectileSpawnPoint->SetupAttachment(TurretHead);

	ActiveTickZone = CreateDefaultSubobject<UTickOptimizer>(TEXT("ActiveZoneForTickFunction"));
	ActiveTickZone->SetupAttachment(TurretBase);
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerPavuk = Cast<APlayerPavuk>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateTurretHead();
}

void ATurret::RotateTurretHead()
{
	if (!PlayerPavuk) return;

	const FRotator CurrentTurretHeadRotation = TurretHead->GetRelativeRotation();

	const FVector PavukLocation = PlayerPavuk->GetActorLocation();
	const FVector TurretHeadLocation = TurretHead->GetComponentLocation();
	const FVector TargetLocation = PavukLocation - TurretHeadLocation;

	const FRotator TargetRotation = FMath::RInterpConstantTo(CurrentTurretHeadRotation, 
		TargetLocation.Rotation(), 
		UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 
		TurretRotationSpeed
	);

	TurretHead->SetRelativeRotation(FRotator(0.f, TargetRotation.Yaw, 0.f));

	if (!GetWorldTimerManager().IsTimerActive(ShootingTimerHandle))
	GetWorldTimerManager().SetTimer(ShootingTimerHandle, this, &ATurret::Shoot, ShootTimer);
}

void ATurret::Shoot()
{
	Super::Shoot();
}