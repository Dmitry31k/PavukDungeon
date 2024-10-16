// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lever.h"
#include "LeverWithTimer.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API ALeverWithTimer : public ALever
{
	GENERATED_BODY()

public:

	virtual void ActivateLever() override;

protected:

	FTimerHandle Deactivator;

	UPROPERTY(EditAnywhere)
	float DeactivateTimer;
	
	void DeactivateLever();
};
