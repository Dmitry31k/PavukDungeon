// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyVisionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyVisionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PAVUKDUNGEON_API IEnemyVisionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual bool CanEnemySeePlayer() { return false; }

	virtual FVector GetPlayerLocation() { return FVector::ZeroVector; }

};
