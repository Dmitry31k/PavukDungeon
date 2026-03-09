// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/DeathInterface.h"
#include "BaseCharacter.generated.h"

class UHealthComponent;
class AProjectile;

UCLASS()
class PAVUKDUNGEON_API ABaseCharacter : public ACharacter, public IDeathInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* DeathParticles;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> ProjectileClass;
	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	UHealthComponent* HealthComponent;

public:

	virtual void HandleDeath() override;

	// DeathInterface start
	virtual UHealthComponent* GetHealthComponent() override;
	virtual FOnActorDeadSignature& GetOnActorDeadDelegate() { return OnActorDead; }
	// DeathInterface end

	virtual void Shoot();
	virtual void MeleeAttack();

	FOnActorDeadSignature OnActorDead;
};