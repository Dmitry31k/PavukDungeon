// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class PAVUKDUNGEON_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* DeathParticles;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;
	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent* ProjectileSpawnPoint;

public:

	virtual void CharacterDied();

	virtual void Shoot();
	virtual void MeleeAttack();

	bool IsWasHitByPlayer = false;

private:

	UFUNCTION()
	void WasHitByPlayer(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

};