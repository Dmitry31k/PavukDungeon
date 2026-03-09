// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Interfaces/EnemyInterface.h"
#include "AIControllerBase.generated.h"

class UBehaviorTree;
enum class EPatrollingType : uint8;

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API AAIControllerBase : public AAIController, public IEnemyInterface
{
	GENERATED_BODY()

public:

	// IEnemyInterface start
	virtual bool CanSeePlayer() override { return bCanSeePlayer; }
	virtual bool WasHitByPlayer() override { return bWasHitByPlayer; }

	virtual FOnPlayerDetectedSignature& GetOnPlayerStartOverlapVision() override { return OnPlayerStartOverlapVision; }
	virtual FOnPlayerDetectedSignature& GetOnPlayerEndOverlapVision() override { return OnPlayerEndOverlapVision; }
	virtual FOnPlayerDetectedSignature& GetOnHitByPlayer() override { return OnHitByPlayer; }

	virtual TArray<AActor*> GetPatrolPts() const { return PatrollingPoints; }

	virtual FVector GetPlayerLocation();

	virtual void SetWasHitByPlayer(bool bWasHit) { bWasHitByPlayer = bWasHit; }
	// IEnemyInterface end

	FOnPlayerDetectedSignature OnPlayerStartOverlapVision;
	FOnPlayerDetectedSignature OnPlayerEndOverlapVision;
	FOnPlayerDetectedSignature OnHitByPlayer;

protected:

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	virtual void HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(EditDefaultsOnly, category = "Bihavior")
	TObjectPtr<UBehaviorTree> BehaviorTreeClass;

	bool bCanSeePlayer { false };
	bool bWasHitByPlayer { false };

	TArray<AActor*> PatrollingPoints;
	EPatrollingType PatrollingType;
};
