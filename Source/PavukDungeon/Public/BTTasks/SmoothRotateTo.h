// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "SmoothRotateTo.generated.h"

/**
 * 
 */

UCLASS()
class PAVUKDUNGEON_API USmoothRotateTo : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	USmoothRotateTo();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 100;

	void SmoothRotate(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds);
};
