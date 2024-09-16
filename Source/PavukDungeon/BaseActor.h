// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseActor.generated.h"

UCLASS()
class PAVUKDUNGEON_API ABaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseActor();

	virtual void ActorDied();

protected:

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* DeathParticles;
	
};
