// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GetPatrolPoint.generated.h"

struct FBTGetPatrolPointMemory : public FBTTaskMemory
{
	int32 PatrolIndex { 0 };
};

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UGetPatrolPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	virtual uint16 GetSpecialMemorySize() const;
	
protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
