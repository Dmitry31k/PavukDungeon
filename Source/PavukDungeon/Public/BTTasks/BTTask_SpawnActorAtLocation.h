// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SpawnActorAtLocation.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UBTTask_SpawnActorAtLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_SpawnActorAtLocation();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	UPROPERTY(EditAnywhere, category = "Spawn")
	FVector CollisionCheckerExtension;

	UPROPERTY(EditAnywhere, category = "Spawn")
	float MinSpawnDistFromCharacter;

	UPROPERTY(EditAnywhere, category = "Spawn")
	float SpawnMultiplyer = 2;

	UPROPERTY(EditAnywhere, category = "Spawn")
	TSubclassOf<class ACharacter> ToSpawnCharacter;

	UPROPERTY(EditAnywhere, category = "Spawn")
	int MaxTryToSpawn = 100;

	void FindPlaceForSpawn(FVector& SpawnAtLocation, FVector& CurrentActorLocation, APawn* OwnerPawn);
	bool WasHit;

	UPROPERTY(EditAnywhere, category = "Spawn")
	class UNiagaraSystem* SpawnParticles;

	UPROPERTY(EditAnywhere, category = "Spawn")
	float SpawnNiagaraSystemZOffset = 10;

	UPROPERTY(EditAnywhere, category = "Spawn")
	float SpawnDelay = 2;

	UFUNCTION()
	void SpawnActorAndFinishTask(UBehaviorTreeComponent* OwnerComp, FVector SpawnAtLocation, FRotator OwnerPawnRotation, class UNiagaraComponent* SpawnedNiagaraSystem = nullptr);
};
