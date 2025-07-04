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
	DroneLineOfSight->ComponentTags.Add(FName("IgnoreDamage"));
}

void AShootingDrone::BeginPlay()
{
	Super::BeginPlay();
	
	DroneLineOfSight->OnComponentBeginOverlap.AddDynamic(this, &AShootingDrone::IsDroneLineOfSightBeginOverlapByPlayer);
	DroneLineOfSight->OnComponentEndOverlap.AddDynamic(this, &AShootingDrone::IsDroneLineOfSightEndOverlapByPlayer);

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