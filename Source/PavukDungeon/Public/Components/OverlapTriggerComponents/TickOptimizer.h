// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/OverlapTriggerComponents/OnPlayerOverlapComponent.h"
#include "TickOptimizer.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class PAVUKDUNGEON_API UTickOptimizer : public UOnPlayerOverlapComponent
{
	GENERATED_BODY()

public:

	UTickOptimizer();

private:

	virtual void PlayerStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp) override;
	virtual void PlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp) override;
	
};
