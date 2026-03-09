// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllers/EnemyAIController.h"
#include "Components/OverlapTriggerComponents/OnPlayerOverlapComponent.h"

void AEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    BindCallbacksToDelegates(InPawn);
}

void AEnemyAIController::BindCallbacksToDelegates(APawn* OwnerPawn)
{
    if (UOnPlayerOverlapComponent* OnPlayerOverlap = OwnerPawn->FindComponentByClass<UOnPlayerOverlapComponent>())
    {
        OnPlayerOverlap->OnStartOverlappedByPlayer.AddUObject(this, &AEnemyAIController::HandleOnPlayerOverlapBegins);
        OnPlayerOverlap->OnEndOverlappedByPlayer.AddUObject(this, &AEnemyAIController::HandleOnPlayerOverlapEnds);
    }
}

void AEnemyAIController::HandleOnPlayerOverlapBegins(AActor* OverlappedActor, UPrimitiveComponent* OverlappedComp, AActor* PlayerActor)
{
    OnPlayerStartOverlapVision.Broadcast(PlayerActor, this);
    bCanSeePlayer = true;
}
void AEnemyAIController::HandleOnPlayerOverlapEnds(AActor* OverlappedActor, UPrimitiveComponent* OverlappedComp, AActor* PlayerActor)
{
    OnPlayerEndOverlapVision.Broadcast(PlayerActor, this);
    bCanSeePlayer = false;
}