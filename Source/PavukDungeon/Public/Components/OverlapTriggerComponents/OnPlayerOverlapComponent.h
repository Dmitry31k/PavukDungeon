// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/OverlapTriggerComponents/OnOverlapSphereComponent.h"
#include "OnPlayerOverlapComponent.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UOnPlayerOverlapComponent : public UOnOverlapSphereComponent
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Triggered on overlap begin with player
	virtual void PlayerStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp);
	// Triggered on overlap end with player
	virtual void PlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp);

	TWeakObjectPtr<AActor> PlayerActor;
};