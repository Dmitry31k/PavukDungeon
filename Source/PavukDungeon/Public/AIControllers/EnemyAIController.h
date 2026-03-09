// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIControllers/AIControllerBase.h"
#include "EnemyAIController.generated.h"


/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API AEnemyAIController : public AAIControllerBase
{
	GENERATED_BODY()

protected:

	virtual void OnPossess(APawn* InPawn);

private:

	void BindCallbacksToDelegates(APawn* OwnerPawn);

	void HandleOnPlayerOverlapBegins(AActor* OverlappedActor, UPrimitiveComponent* OverlappedComp, AActor* PlayerActor);
	void HandleOnPlayerOverlapEnds(AActor* OverlappedActor, UPrimitiveComponent* OverlappedComp, AActor* PlayerActor);


};
