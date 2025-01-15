// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_DroneWithLaser.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API AAIController_DroneWithLaser : public AAIController
{
	GENERATED_BODY()

public:
	
	FVector FirstMoveOffset_AIController;
	FVector SecondMoveOffset_AIController;
	FVector ThirdtMoveOffset_AIController;
	FVector FourthMoveOffset_AIController;
	FVector FifthMoveOffset_AIController;
	
	bool MustRotating_AIController;
	bool MustRotatingAndMoving_AIController;
	bool MustMoving_AIController;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, category = "Behavior")
	class UBehaviorTree* DroneWithLaserBehaviorTreeClass;

	FTimerHandle SetVariablesTimer;

	//Function that set blackboard variables
	void SetVariabledIntoBlackboard();

	FVector StartLocation;

};
