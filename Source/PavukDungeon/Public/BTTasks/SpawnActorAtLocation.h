// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "SpawnActorAtLocation.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API USpawnActorAtLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:

	USpawnActorAtLocation();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	UPROPERTY(EditAnywhere, category = "Spawn")
	FVector CollisionCheckerExtension { 40.f, 60.f, 25.f };

	UPROPERTY(EditAnywhere, category = "Spawn")
	float MinSpawnDistFromCharacter { 75.f };

	UPROPERTY(EditAnywhere, category = "Spawn")
	TSubclassOf<ACharacter> ToSpawnCharacter;

	UPROPERTY(EditAnywhere, category = "Spawn")
	int32 MaxSpawnAttempts { 100 };

	UPROPERTY(EditAnywhere, category = "Spawn")
	TObjectPtr<UNiagaraSystem> SpawnParticles;

	UPROPERTY(EditAnywhere, category = "Spawn")
	float SpawnNiagaraSystemZOffset { -50 };

	UPROPERTY(EditAnywhere, category = "Spawn")
	float SpawnDelay { 2 };

	void SpawnActorAndFinishTask(TWeakObjectPtr<UBehaviorTreeComponent> OwnerComp, FVector SpawnAtLocation, FRotator OwnerPawnRotation, UNiagaraComponent* SpawnedNiagaraSystem = nullptr);
	bool FindPlaceForSpawn(FVector& SpawnAtLocation, FVector& CurrentActorLocation, APawn* OwnerPawn);
};
