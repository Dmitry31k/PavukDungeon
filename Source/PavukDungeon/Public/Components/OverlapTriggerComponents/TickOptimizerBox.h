// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/OverlapTriggerComponents/OnOverlapBoxComponent.h"
#include "TickOptimizerBox.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class PAVUKDUNGEON_API UTickOptimizerBox : public UOnOverlapBoxComponent
{
	GENERATED_BODY()

public:

	UTickOptimizerBox();

private:

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
};
