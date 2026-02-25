// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseActor.h"
#include "BaseEnemyActor.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API ABaseEnemyActor : public ABaseActor
{
	GENERATED_BODY()

public:

	ABaseEnemyActor();
	
	virtual void HandleDeath() override;

	// DeathInterface start
	virtual UHealthComponent* GetHealthComponent() override;
	// DeathInterface end

protected:

	virtual void BeginPlay() override;

	virtual void Shoot();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* ProjectileSpawnPoint;

private:
	
};