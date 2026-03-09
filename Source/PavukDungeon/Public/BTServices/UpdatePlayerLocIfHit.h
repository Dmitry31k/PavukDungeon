// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "UpdatePlayerLocIfHit.generated.h"

struct FBTUpdatePlayerLocIfHitMemory : public FBTAuxiliaryMemory
{
	FDelegateHandle BoundLambdaHandle;
};

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UUpdatePlayerLocIfHit : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UUpdatePlayerLocIfHit();

	virtual uint16 GetSpecialMemorySize() const override;

protected:

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};