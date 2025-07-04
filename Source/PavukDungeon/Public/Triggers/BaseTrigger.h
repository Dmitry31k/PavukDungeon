// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "BaseTrigger.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API ABaseTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:

	ABaseTrigger();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OverlapBegin(AActor* OverlappedActor, AActor* OverlappingActor);
	UFUNCTION()
	virtual void OverlapEnd(AActor* OverlappedActor, AActor* OverlappingActor);
	
};
