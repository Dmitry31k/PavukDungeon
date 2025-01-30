// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MoveToWithConstDist.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UBTTask_MoveToWithConstDist : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTTask_MoveToWithConstDist();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	UPROPERTY()
	class APawn* OwnerPawn;
	UPROPERTY()
	class AAIController* OwnerController;

	UPROPERTY(EditAnywhere)
	float DistFromTarget = 500;

	FVector TargetLocation;
};
