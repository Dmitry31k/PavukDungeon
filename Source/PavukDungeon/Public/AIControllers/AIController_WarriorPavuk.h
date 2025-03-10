// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_WarriorPavuk.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API AAIController_WarriorPavuk : public AAIController
{
	GENERATED_BODY()

protected:

	virtual void OnPossess(APawn* InPawn) override;

private:

	UPROPERTY(EditDefaultsOnly, category = "Bihavior")
	class UBehaviorTree* WarriorPavukBehaviorTreeClass;
	
};
