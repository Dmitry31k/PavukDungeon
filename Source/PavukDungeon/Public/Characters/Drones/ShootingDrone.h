// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Drones/BaseDrone.h"
#include "Interfaces/LightInterface.h"
#include "ShootingDrone.generated.h"

class USpotLightComponent;
class UOnPlayerOverlapComponent;

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API AShootingDrone : public ABaseDrone, public ILightInterface
{
	GENERATED_BODY()

public:

	AShootingDrone();

	// LightInterface start
	TArray<USpotLightComponent*> GetAllLightComps() { return {VisionBacklight}; }
	// LightInterface end

private:

	// Component that rects when player overlaps it
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UOnPlayerOverlapComponent> DroneVision;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USpotLightComponent> VisionBacklight;
};
