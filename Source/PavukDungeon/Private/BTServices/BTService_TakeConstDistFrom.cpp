// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServices/BTService_TakeConstDistFrom.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

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

    UNavigationSystemV1* InNavMesh = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    UNavigationPath* Path = InNavMesh->FindPathToLocationSynchronously(GetWorld(), CurrentOwnerLocation, MoveToTarget);

    if (Path && Path->IsValid() && Path->GetPathLength() > 0)
    {
        OwnerController->MoveTo(MoveToTarget);
    }
    else
    {
        GoToRandomPointWithDistFromTarget(InNavMesh, CurrentOwnerLocation, TargetLocation);
    }
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

void UBTService_TakeConstDistFrom::GoToRandomPointWithDistFromTarget(UNavigationSystemV1* InNavMesh, FVector CurrentOwnerLocation, FVector TargetLocation)
{
    bool bFoundValidPath = false;

    for (size_t i = 0; i <= LimitRandomPathGen; i++)
    {
        FNavLocation ResultRandomLocation;
            
        bFoundValidPath = InNavMesh->GetRandomPointInNavigableRadius(CurrentOwnerLocation, DistFromTarget * 2, ResultRandomLocation);

        if (bFoundValidPath)
        {
            FVector MoveToRandomLocation = FVector(ResultRandomLocation.Location.X, ResultRandomLocation.Location.Y, CurrentOwnerLocation.Z);
                
            if (FVector::Dist(MoveToRandomLocation, TargetLocation) >= DistFromTarget)
            {
                OwnerController->MoveTo(MoveToRandomLocation);
                break;
            }
        }
    }
}