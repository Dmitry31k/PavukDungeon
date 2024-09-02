// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MoveToWithoutRotation.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UBTTask_MoveToWithoutRotation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTTask_MoveToWithoutRotation();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	UPROPERTY(EditAnywhere)
	float MovingSpeed = 150;

	UPROPERTY()
	class AAIController* OwnerAIController;

	UPROPERTY()
	APawn* OwnerPawn;

};
