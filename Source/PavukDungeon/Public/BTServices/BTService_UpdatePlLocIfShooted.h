// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdatePlLocIfShooted.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UBTService_UpdatePlLocIfShooted : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTService_UpdatePlLocIfShooted();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	void UpdatePlayerLocationIfShootedByPlayer(UBehaviorTreeComponent& OwnerComp, class ABaseCharacter* OwnerBaseCharacterPawn, APawn* PlayerPawn);

};