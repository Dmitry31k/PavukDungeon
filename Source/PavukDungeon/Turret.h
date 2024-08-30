// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

UCLASS()
class PAVUKDUNGEON_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* TurretBase;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* TurretHead;

	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY()
	class APlayerPavuk* PlayerPavuk;

	UPROPERTY(EditAnywhere, category = "combat")
	float MaxDistanceRange = 1000;

	UPROPERTY(EditAnywhere, category = "combat")
	float TurretRotationSpeed = 20;

	UPROPERTY(EditAnywhere, category = "combat")
	float ShootTimer = 0;

	void RotateTurretHead();
	void Shoot();
	
	FTimerHandle ShootingTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;
	
	bool InFireRange = false;
};