// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_TakeConstDistFrom.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UBTService_TakeConstDistFrom : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:

	UBTService_TakeConstDistFrom();

protected:

	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory) override;

private:

	UPROPERTY()
	APawn* PlayerPawn;
	UPROPERTY()
	AAIController* OwnerController;

	UPROPERTY(EditAnywhere, category = "Combat")
	float DistFromTarget = 500;
};