// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SmoothRotateTo.generated.h"

/**
 * 
 */
struct FBTSmoothRotateToNodeMemory : public FBTTaskMemory
{
	FRotator CurrentRotation;
	FRotator TargetRotation;
};

UCLASS()
class PAVUKDUNGEON_API UBTTask_SmoothRotateTo : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTTask_SmoothRotateTo();

	virtual uint16 GetInstanceMemorySize() const override;

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 100;

	UPROPERTY()
	class AAIController* OwnerController;

	UPROPERTY()
	class APawn* OwnerPawn;

	void SmoothRotate(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds, FBTSmoothRotateToNodeMemory* MyNodeMemory);
};
