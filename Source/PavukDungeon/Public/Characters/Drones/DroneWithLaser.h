// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Drones/BaseDrone.h"
#include "DroneWithLaser.generated.h"

class UNiagaraComponent;
class UTickOptimizer;
class UPatrollingComponent;

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API ADroneWithLaser : public ABaseDrone
{
	GENERATED_BODY()
	
public:
	
	ADroneWithLaser();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, category = "Combat")
	float LaserLength = 500;

	UPROPERTY(EditDefaultsOnly, category = "Combat")
	float LaserDamage = 100;

	bool IsBlockingLaser = false;

	FHitResult LineTraceHitResult;

	UPROPERTY()
	class APlayerPavuk* PlayerPavuk;

	void LaserShoot();
	void CheckIfPlayerTouchedLaser();

	UPROPERTY(EditDefaultsOnly, category = "Combat")
	UTickOptimizer* ActiveTickZone;

	UPROPERTY(EditDefaultsOnly, category = "Visual")
	UNiagaraComponent* LaserNiagaraComponent;

	UPROPERTY(EditDefaultsOnly, category = "Visual")
	UNiagaraSystem* LaserFlashNiagaraSystem;

	UPROPERTY(VisibleAnywhere, category = "Combat")
	TObjectPtr<UPatrollingComponent> PatrollingComponent;
};
