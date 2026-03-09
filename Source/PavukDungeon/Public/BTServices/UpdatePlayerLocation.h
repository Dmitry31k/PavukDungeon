// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "UpdatePlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UUpdatePlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UUpdatePlayerLocation();
	
protected:

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// The game has only one player, so we store the PlayerPawn directly
	// so all nodes share the same reference
	UPROPERTY()
	TWeakObjectPtr<APawn> PlayerPawn;

};
