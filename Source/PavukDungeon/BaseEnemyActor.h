// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
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

private:

	UPROPERTY(EditAnywhere)
	class UHealthComponent* HealthComponent;
	
};
