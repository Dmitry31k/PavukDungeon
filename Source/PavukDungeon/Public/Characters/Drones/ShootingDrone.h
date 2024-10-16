// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Drones/BaseDrone.h"
#include "ShootingDrone.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API AShootingDrone : public ABaseDrone
{
	GENERATED_BODY()

public:

	AShootingDrone();

	virtual void Shoot() override;

	bool IsDroneLineOfSightOverlappedByPlayer = false;
	bool IsWasShotedByPlayer = false;

	UPROPERTY(EditAnywhere)
	class USpotLightComponent* VisionBacklight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void IsDroneLineOfSightBeginOverlapByPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void IsDroneLineOfSightEndOverlapByPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void DroneWasShotedByPlayer(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* DroneLineOfSight;	
	
};
