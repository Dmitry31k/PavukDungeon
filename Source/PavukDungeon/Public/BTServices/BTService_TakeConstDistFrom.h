// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_TakeConstDistFrom.generated.h"

class UNavigationSystemV1;
class UNavigationPath;

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UBTService_TakeConstDistFrom : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:

	UBTService_TakeConstDistFrom();

protected:

	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory) override;

private:

	UPROPERTY()
	APawn* PlayerPawn;
	UPROPERTY()
	AAIController* OwnerController;

	UPROPERTY(EditAnywhere, category = "Combat")
	float DistFromTarget = 500;

	// Number of points in a circle around the AI to evaluate for movement
	UPROPERTY(EditAnywhere, category = "Combat")
    int32 NumPoints = 8;

	UNavigationSystemV1* CurrentNavMesh;

	// Attempts to find a within a certain radius and moves the AI to that location.
	void GoToSmartPointAroundTarget(UNavigationSystemV1* InNavMesh, FVector CurrentOwnerLocation, FVector TargetLocation);
	
	/**
 	* Calculates a path to the target location while ensuring the AI maintains the specified distance.
	* If the path is valid, it returns the path and the final position for the AI to move towards.
 	*/
	UNavigationPath* FindPathInNavMeshFromTarget(UNavigationSystemV1* InNavMesh, FVector TargetLocation, FVector CurrentOwnerLocation, FVector& MoveToTarget);
};