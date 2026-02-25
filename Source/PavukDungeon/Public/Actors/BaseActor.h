// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/DeathInterface.h"
#include "BaseActor.generated.h"

class UHealthComponent;

UCLASS()
class PAVUKDUNGEON_API ABaseActor : public AActor, public IDeathInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseActor();

	// DeathInterface start
	virtual void HandleDeath() override;
	virtual FOnActorDeadSignature& GetOnActorDeadDelegate() override { return OnActorDead; }
	// DeathInterface end

	UPROPERTY(BlueprintAssignable)
	FOnActorDeadSignature OnActorDead;

protected:

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* DeathParticles;
	
};
