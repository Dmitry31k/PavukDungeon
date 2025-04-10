// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EnemyActors/OverlapBoxActors/Turret.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Pavuks/PlayerPavuk.h"
#include "Math/UnrealMathUtility.h"
#include "Components/SceneComponent.h"
#include "Actors/EnemyActors/Projectile.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TurretBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	TurretHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawner"));

	TurretBase->SetupAttachment(RootComponent);
	TurretHead->SetupAttachment(TurretBase);
	ProjectileSpawnPoint->SetupAttachment(TurretHead);
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerPavuk = Cast<APlayerPavuk>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

void ATurret::RotateTurretHead()
{
	if (!IsActivated)
	{
		return;
	}

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
			InFireRange = true;
		}
		else
		{
			InFireRange = false;
		}
	}

	GetWorldTimerManager().SetTimerForNextTick(this, &ATurret::RotateTurretHead);
}

void ATurret::Shoot()
{
	if (InFireRange && ProjectileClass && PlayerPavuk)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, 
			ProjectileSpawnPoint->GetComponentLocation(), 
			ProjectileSpawnPoint->GetComponentRotation()
		);

		Projectile->SetOwner(this);
	}
}

void ATurret::TriggerBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<APlayerPavuk>(OtherActor))
	{
		IsActivated = true;
		RotateTurretHead();
		GetWorldTimerManager().SetTimer(ShootingTimerHandle, this, &ATurret::Shoot, ShootTimer, true);
	}
}

void ATurret::TriggerBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<APlayerPavuk>(OtherActor))
	{
		IsActivated = false;
		GetWorldTimerManager().ClearTimer(ShootingTimerHandle);
	}
}