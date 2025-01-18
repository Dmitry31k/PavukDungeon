// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UBTTask_MeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_MeleeAttack();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
	
};
