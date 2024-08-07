// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ShootD.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UBTTask_ShootD : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_ShootD();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
