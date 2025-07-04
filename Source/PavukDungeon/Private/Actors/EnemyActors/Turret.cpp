// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EnemyActors/Turret.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Pavuks/PlayerPavuk.h"
#include "Math/UnrealMathUtility.h"
#include "Components/SceneComponent.h"
#include "Actors/EnemyActors/Projectile.h"
#include "Components/OverlapTriggerComponents/TickOptimizerBox.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	TurretHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawner"));

	TurretBase->SetupAttachment(RootComponent);
	TurretHead->SetupAttachment(TurretBase);
	ProjectileSpawnPoint->SetupAttachment(TurretHead);

	ActiveTickZone = CreateDefaultSubobject<UTickOptimizerBox>(TEXT("ActiveZoneForTickFunction"));
	ActiveTickZone->SetupAttachment(TurretBase);
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerPavuk = Cast<APlayerPavuk>(UGameplayStatics::GetPlayerCharacter(this, 0));
	SetActorTickEnabled(false);
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateTurretHead();
}

void ATurret::RotateTurretHead()
{
	FRotator CurrentTurretHeadRotation = TurretHead->GetRelativeRotation();

	if (PlayerPavuk)
	{
		FVector PavukLocation = PlayerPavuk->GetActorLocation();
		FVector TurretHeadLocation = TurretHead->GetComponentLocation();

		if (FVector::Dist(PavukLocation, TurretHeadLocation) <= MaxDistanceRange)
		{
			FVector TargetLocation = PavukLocation - TurretHeadLocation;

			FRotator TargetRotation = FMath::RInterpConstantTo(CurrentTurretHeadRotation, 
				TargetLocation.Rotation(), 
				UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 
				TurretRotationSpeed
			);

			TurretHead->SetRelativeRotation(FRotator(0.f, TargetRotation.Yaw, 0.f));

			if (!bWasSetTimer)
			{
				GetWorldTimerManager().SetTimer(ShootingTimerHandle, this, &ATurret::Shoot, ShootTimer, true);
				bWasSetTimer = true;
			}
		}
		else
		{
			GetWorldTimerManager().ClearTimer(ShootingTimerHandle);
			bWasSetTimer = false;
		}
	}
}

void ATurret::Shoot()
{
	if (ProjectileClass && PlayerPavuk)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, 
			ProjectileSpawnPoint->GetComponentLocation(), 
			ProjectileSpawnPoint->GetComponentRotation()
		);

		Projectile->SetOwner(this);
	}
}