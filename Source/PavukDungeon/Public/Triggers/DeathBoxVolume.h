// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "DeathBoxVolume.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API ADeathBoxVolume : public ATriggerBox
{
	GENERATED_BODY()
	
public: 

	ADeathBoxVolume();

protected:

	virtual void BeginPlay();

private:

	UPROPERTY(EditAnywhere, category = "Damage")
	float DamageForPlayer = 100;

	UFUNCTION()
	void OverlapBegin(AActor* OverlappedActor, AActor* OverlappingActor);

	UFUNCTION()
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void DamageOverlappedActor(AActor* DamagedActor);

	FTimerHandle DamageTimer;
	FTimerDelegate DamageTimerDelegate;

	UPROPERTY(EditAnywhere, category = "Damage")
	float ApplyDamageTimer = 1;

	UPROPERTY()
	class APlayerPavuk* PlayerPavuk;

};
