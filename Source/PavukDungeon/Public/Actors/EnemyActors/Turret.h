// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyActor.h"
#include "Turret.generated.h"

class APlayerPavuk;
class UTickOptimizerBox;

UCLASS()
class PAVUKDUNGEON_API ATurret : public ABaseEnemyActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* TurretBase;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* TurretHead;

	UPROPERTY()
	APlayerPavuk* PlayerPavuk;

	UPROPERTY(EditAnywhere, category = "Combat")
	float MaxDistanceRange = 1000;

	UPROPERTY(EditAnywhere, category = "Combat")
	float TurretRotationSpeed = 20;

	UPROPERTY(EditAnywhere, category = "Combat")
	float ShootTimer = 0;

	void RotateTurretHead();
	void Shoot() override;
	
	FTimerHandle ShootingTimerHandle;

	bool bWasSetTimer = false;

	UPROPERTY(EditDefaultsOnly, category = "Combat")
	UTickOptimizerBox* ActiveTickZone;
};