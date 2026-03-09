// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServices/UpdatePlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UUpdatePlayerLocation::UUpdatePlayerLocation()
{
    NodeName = "Update location if see player";

    bNotifyBecomeRelevant = true;
}

void UUpdatePlayerLocation::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::OnBecomeRelevant(OwnerComp, NodeMemory);

    PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
}

void UUpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if (!PlayerPawn.Get())
    {
        PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
        return;
    }

    AAIController* AIOwner = OwnerComp.GetAIOwner();

    if (AIOwner->LineOfSightTo(PlayerPawn.Get()))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}