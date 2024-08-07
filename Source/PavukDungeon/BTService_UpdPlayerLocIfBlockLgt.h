// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdPlayerLocIfBlockLgt.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UBTService_UpdPlayerLocIfBlockLgt : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTService_UpdPlayerLocIfBlockLgt();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
