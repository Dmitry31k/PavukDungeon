// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "UpdValueWithPlayerLoc.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UUpdValueWithPlayerLoc : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UUpdValueWithPlayerLoc();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	UPROPERTY(EditAnywhere)
	FName PlayerLocationValueName { "PlayerLocation" };
};
