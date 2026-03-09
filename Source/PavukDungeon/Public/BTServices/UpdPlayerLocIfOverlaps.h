// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "Interfaces/EnemyInterface.h"
#include "UpdPlayerLocIfOverlaps.generated.h"

class AAIConstroller;

struct FBTUpdPlayerLocIfOverlapsMemory : public FBTAuxiliaryMemory
{
	TMap<FDelegateHandle, FOnPlayerDetectedSignature*> LambdasToDelegats;
	bool bCanSeePlayer { false };
};

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UUpdPlayerLocIfOverlaps : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UUpdPlayerLocIfOverlaps();

	uint16 GetSpecialMemorySize() const override;

protected:

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	UPROPERTY()
	TWeakObjectPtr<AActor> TargetPlayer;

	void InitLambdasToDelegats(AAIController* OwnerController, FBTUpdPlayerLocIfOverlapsMemory* NodeMemory);
};
