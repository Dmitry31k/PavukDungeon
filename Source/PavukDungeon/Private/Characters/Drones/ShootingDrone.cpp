// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Drones/ShootingDrone.h"
#include "Components/OverlapTriggerComponents/OnPlayerOverlapComponent.h"
#include "Characters/Pavuks/PlayerPavuk.h"
#include "Components/SpotLightComponent.h"

AShootingDrone::AShootingDrone()
{
    VisionBacklight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Vision backlight"));
	VisionBacklight->SetupAttachment(RootComponent);

    DroneVision = CreateDefaultSubobject<UOnPlayerOverlapComponent>(TEXT("Drone line of sight"));
	DroneVision->SetupAttachment(RootComponent);
	DroneVision->ComponentTags.Add(FName("IgnoreDamage"));
}

void AShootingDrone::BeginPlay()
{
	Super::BeginPlay();

	DroneVision->OnStartOverlappedByPlayer.AddDynamic(this, &AShootingDrone::HandleDroneVisionOverlapBegins);
	DroneVision->OnEndOverlappedByPlayer.AddDynamic(this, &AShootingDrone::HandleDroneVisionOverlapEnds);
}

void AShootingDrone::Shoot()
{
    Super::Shoot();
}

void AShootingDrone::HandleDroneVisionOverlapBegins(AActor* OverlappedActor, UPrimitiveComponent* OverlappedComponent)
{
	bCanSeePlayer = true;
}
void AShootingDrone::HandleDroneVisionOverlapEnds(AActor* OverlappedActor, UPrimitiveComponent* OverlappedComponent)
{
	bCanSeePlayer = false;
}