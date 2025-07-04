// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Triggers/BaseTrigger.h"
#include "PlayerTrigger.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API APlayerTrigger : public ABaseTrigger
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	virtual void OverlapBegin(AActor* OverlappedActor, AActor* OverlappingActor) override;
	virtual void OverlapEnd(AActor* OverlappedActor, AActor* OverlappingActor) override;

	virtual void PlayerStartOverlap(AActor* OverlappedActor, AActor* OverlappingActor);
	virtual void PlayerEndOverlap(AActor* OverlappedActor, AActor* OverlappingActor);

	TWeakObjectPtr<AActor> PlayerActor;
	
};
