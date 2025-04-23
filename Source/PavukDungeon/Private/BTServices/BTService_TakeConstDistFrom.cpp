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

    FVector MoveToTarget;
    FVector CurrentOwnerLocation = OwnerController->GetPawn()->GetActorLocation();

    UNavigationPath* FoundPath = FindPathInNavMeshFromTarget(CurrentNavMesh, TargetLocation, CurrentOwnerLocation, MoveToTarget);

    if (FoundPath->IsValid() && FoundPath->GetPathLength() > 0)
    {
        OwnerController->MoveTo(MoveToTarget);
    }
    else
    {
        GoToSmartPointAroundTarget(CurrentNavMesh, CurrentOwnerLocation, TargetLocation);
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

    CurrentNavMesh = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

    OwnerController->SetFocus(PlayerPawn);
}

void UBTService_TakeConstDistFrom::OnCeaseRelevant(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory)
{
    Super::OnCeaseRelevant(OwnerComp, NodeMemory);

    if (!OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
    {
        OwnerController->ClearFocus(EAIFocusPriority::Gameplay);
    }
}

UNavigationPath* UBTService_TakeConstDistFrom::FindPathInNavMeshFromTarget(UNavigationSystemV1* InNavMesh, FVector TargetLocation, FVector CurrentOwnerLocation, FVector& MoveToTarget)
{
    if (InNavMesh == nullptr)
    {
        return nullptr;
    }

    FVector DirectionToTarget = TargetLocation - CurrentOwnerLocation;
    DirectionToTarget.Normalize();
    
    MoveToTarget = TargetLocation - DirectionToTarget * DistFromTarget;
    return InNavMesh->FindPathToLocationSynchronously(GetWorld(), CurrentOwnerLocation, MoveToTarget);
}

void UBTService_TakeConstDistFrom::GoToSmartPointAroundTarget(UNavigationSystemV1* InNavMesh, FVector CurrentOwnerLocation, FVector TargetLocation)
{
    const float AngleStep = 360.f / NumPoints;

    TArray<FVector> CandidatePoints;

    for (int i = 0; i < NumPoints; ++i)
    {
        float AngleRad = FMath::DegreesToRadians(i * AngleStep);
        FVector Offset = FVector(FMath::Cos(AngleRad), FMath::Sin(AngleRad), 0.f) * DistFromTarget;
        FVector TestPoint = TargetLocation + Offset;

        // Navigation check
        FNavLocation NavLoc;
        if (InNavMesh->ProjectPointToNavigation(TestPoint, NavLoc))
        {
            CandidatePoints.Add(NavLoc.Location);
        }
    }

    // Sort by distance from current AIOwner location
    CandidatePoints.Sort([&](const FVector& Min, const FVector& Max)
    {
        return FVector::DistSquared(CurrentOwnerLocation, Min) < FVector::DistSquared(CurrentOwnerLocation, Max);
    });

    for (const FVector& Point : CandidatePoints)
    {
        UNavigationPath* Path = InNavMesh->FindPathToLocationSynchronously(GetWorld(), CurrentOwnerLocation, Point);

        if (Path && Path->IsValid() && Path->GetPathLength() > 0)
        {
            OwnerController->MoveTo(Point);
            return;
        }
    }
}