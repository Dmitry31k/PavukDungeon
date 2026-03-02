// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyActor.h"
#include "Turret.generated.h"

class APlayerPavuk;
class UTickOptimizer;

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
	TObjectPtr<UStaticMeshComponent> TurretBase;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> TurretHead;

	UPROPERTY()
	APlayerPavuk* PlayerPavuk;

	UPROPERTY(EditAnywhere, category = "Combat")
	float TurretRotationSpeed { 80 };

	UPROPERTY(EditAnywhere, category = "Combat")
	float ShootTimer { 3 };

	void RotateTurretHead();
	void Shoot() override;
	
	FTimerHandle ShootingTimerHandle;

	UPROPERTY(EditAnywhere, category = "Combat")
	TObjectPtr<UTickOptimizer> ActiveTickZone;
};