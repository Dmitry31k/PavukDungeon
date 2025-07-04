// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/OverlapTriggerComponents/OnPlayerOverlapComponent.h"
#include "TickOptimizerBox.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class PAVUKDUNGEON_API UTickOptimizerBox : public UOnPlayerOverlapComponent
{
	GENERATED_BODY()

public:

	UTickOptimizerBox();

private:

	virtual void PlayerStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp) override;
	virtual void PlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp) override;
	
};
