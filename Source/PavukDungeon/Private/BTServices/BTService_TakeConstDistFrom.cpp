// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServices/BTService_TakeConstDistFrom.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"

UBTService_TakeConstDistFrom::UBTService_TakeConstDistFrom()
{
    NodeName = "Take const dist from target";

    bNotifyBecomeRelevant = true;
    bCreateNodeInstance = true;
    bNotifyTick = true;
    bNotifyCeaseRelevant = true;
}

void UBTService_TakeConstDistFrom::TickNode(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory, float  DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if (OwnerController == nullptr || PlayerPawn == nullptr)
    {
        return;
    }

    FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
    FVector CurrentOwnerLocation = OwnerController->GetPawn()->GetActorLocation();

    FVector DirectionToTarget = TargetLocation - CurrentOwnerLocation;
    DirectionToTarget.Normalize();
    
    FVector MoveToTarget = TargetLocation - DirectionToTarget * DistFromTarget;
    OwnerController->MoveTo(MoveToTarget);
}

void UBTService_TakeConstDistFrom::OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory)
{
    Super::OnBecomeRelevant(OwnerComp, NodeMemory);

    OwnerController = OwnerComp.GetAIOwner();
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (OwnerController == nullptr || PlayerPawn == nullptr)
    {
        return;
    }

    OwnerController->SetFocus(PlayerPawn);
}

void UBTService_TakeConstDistFrom::OnCeaseRelevant(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory)
{
    Super::OnCeaseRelevant(OwnerComp, NodeMemory);

    OwnerController->ClearFocus(EAIFocusPriority::Gameplay);
}