// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Drones/ShootingDrone.h"
#include "Components/SphereComponent.h"
#include "Characters/Pavuks/PlayerPavuk.h"
#include "Components/SpotLightComponent.h"

AShootingDrone::AShootingDrone()
{
    VisionBacklight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Vision backlight"));
	VisionBacklight->SetupAttachment(RootComponent);

    DroneLineOfSight = CreateDefaultSubobject<USphereComponent>(TEXT("Drone line of sight"));
	DroneLineOfSight->SetupAttachment(RootComponent);
}

void AShootingDrone::BeginPlay()
{
	Super::BeginPlay();
	
	DroneLineOfSight->OnComponentBeginOverlap.AddDynamic(this, &AShootingDrone::IsDroneLineOfSightBeginOverlapByPlayer);
	DroneLineOfSight->OnComponentEndOverlap.AddDynamic(this, &AShootingDrone::IsDroneLineOfSightEndOverlapByPlayer);
	OnTakeAnyDamage.AddDynamic(this, &AShootingDrone::DroneWasShotedByPlayer);
}

void AShootingDrone::Shoot()
{
    Super::Shoot();
}

void AShootingDrone::IsDroneLineOfSightBeginOverlapByPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<APlayerPavuk>(OtherActor))
	{
		IsDroneLineOfSightOverlappedByPlayer = true;
	}
}

void AShootingDrone::IsDroneLineOfSightEndOverlapByPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<APlayerPavuk>(OtherActor))
	{
		IsDroneLineOfSightOverlappedByPlayer = false;
	}
}

void AShootingDrone::DroneWasShotedByPlayer(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Cast<APlayerPavuk>(DamageCauser->GetOwner()))
	{
		IsWasShotedByPlayer = true;
	}
}