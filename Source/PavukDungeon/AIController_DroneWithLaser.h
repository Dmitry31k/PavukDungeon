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


protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* DroneWithLaserBehaviorTree;

};
