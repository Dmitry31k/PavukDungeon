// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChangeLightColor.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UChangeLightColor : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UChangeLightColor();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	UPROPERTY(EditAnywhere)
	FColor NewColor;

};
