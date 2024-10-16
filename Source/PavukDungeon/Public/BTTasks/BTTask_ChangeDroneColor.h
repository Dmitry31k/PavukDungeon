// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ChangeDroneColor.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UBTTask_ChangeDroneColor : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTTask_ChangeDroneColor();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	UPROPERTY(EditAnywhere)
	FColor NewColor;

};
