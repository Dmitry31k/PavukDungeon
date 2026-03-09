// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

class AAIController;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerDetectedSignature, AActor* /* Detected Player */, AAIController* /* Detection Controller */);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PAVUKDUNGEON_API IEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual bool CanSeePlayer() { return false; }
	virtual bool WasHitByPlayer() { return false; }
	virtual FVector GetPlayerLocation() { return FVector::ZeroVector; }

	virtual TArray<AActor*> GetPatrolPts() const { return TArray<AActor*>(); }

	virtual FOnPlayerDetectedSignature& GetOnPlayerStartOverlapVision() = 0;
	virtual FOnPlayerDetectedSignature& GetOnPlayerEndOverlapVision() = 0;
	virtual FOnPlayerDetectedSignature& GetOnHitByPlayer() = 0;

	virtual void SetWasHitByPlayer(bool bWasHit) = 0;
};
