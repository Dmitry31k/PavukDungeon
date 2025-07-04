// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Triggers/PlayerTrigger.h"
#include "DeathBoxVolume.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API ADeathBoxVolume : public APlayerTrigger
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, category = "Damage")
	float DamageForPlayer = 100;

	virtual void PlayerStartOverlap(AActor* OverlappedActor, AActor* OverlappingActor) override;
	virtual void PlayerEndOverlap(AActor* OverlappedActor, AActor* OverlappingActor) override;

	void DamagePlayer();

	FTimerHandle DamageTimer;

	UPROPERTY(EditAnywhere, category = "Damage")
	float ApplyDamageTimer = 1;

};
