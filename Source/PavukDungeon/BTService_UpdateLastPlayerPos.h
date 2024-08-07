// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateLastPlayerPos.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UBTService_UpdateLastPlayerPos : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTService_UpdateLastPlayerPos();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
