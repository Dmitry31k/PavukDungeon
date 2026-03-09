// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UMeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UMeleeAttack();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
	
};
