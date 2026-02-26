// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Drones/BaseDrone.h"
#include "ShootingDrone.generated.h"

class USpotLightComponent;
class UOnPlayerOverlapComponent;

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API AShootingDrone : public ABaseDrone
{
	GENERATED_BODY()

public:

	AShootingDrone();

	UPROPERTY(EditAnywhere)
	TObjectPtr<USpotLightComponent> VisionBacklight;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void HandleDroneVisionOverlapBegins(AActor* OverlappedActor, UPrimitiveComponent* OverlappedComponent);
	UFUNCTION()
	virtual void HandleDroneVisionOverlapEnds(AActor* OverlappedActor, UPrimitiveComponent* OverlappedComponent);

private:

	// Component that rects when player overlaps it
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UOnPlayerOverlapComponent> DroneVision;

	virtual void Shoot() override;	
};
