// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplePlatform.h"
#include "OverlapEventPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API AOverlapEventPlatform : public AMultiplePlatform
{
	GENERATED_BODY()
	
public:

	AOverlapEventPlatform();

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleDefaultsOnly)
	class UBoxComponent* HitBox;

	UFUNCTION()
	void OverlapBegin(AActor* OverlappedActor, AActor* OverlappingActor);

	UPROPERTY(EditAnywhere, category = "movement")
	float DestructionTimer;
	
	FTimerHandle DestructingPlatform;

	void DestructPlatform();
};
