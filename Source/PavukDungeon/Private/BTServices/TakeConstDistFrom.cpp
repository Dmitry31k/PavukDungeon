// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServices/TakeConstDistFrom.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

UTakeConstDistFrom::UTakeConstDistFrom()
{
    NodeName = "Take const dist from target";

    bNotifyBecomeRelevant = true;
    bNotifyTick = true;
    bNotifyCeaseRelevant = true;
}

void UTakeConstDistFrom::TickNode(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory, float  DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if (!PlayerPawn.Get())
    {
        PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        return;
    }

    AAIController* AIOwner = OwnerComp.GetAIOwner();

    FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
    FVector MoveToTarget;
    FVector CurrentOwnerLocation = AIOwner->GetPawn()->GetActorLocation();

    if (UNavigationSystemV1* CurrentNavMesh = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()))
    {
        UNavigationPath* FoundPath = FindPathInNavMeshFromTarget(CurrentNavMesh, TargetLocation, CurrentOwnerLocation, MoveToTarget);

        if (FoundPath->IsValid() && FoundPath->GetPathLength() > 0)
        {
            AIOwner->MoveTo(MoveToTarget);
        }
        else
        {
            GoToSmartPointAroundTarget(CurrentNavMesh, AIOwner, CurrentOwnerLocation, TargetLocation);
        }
    }
}

void UTakeConstDistFrom::OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory)
{
    Super::OnBecomeRelevant(OwnerComp, NodeMemory);

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn.Get()) return;

    OwnerComp.GetAIOwner()->SetFocus(PlayerPawn.Get());
}

void UTakeConstDistFrom::OnCeaseRelevant(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory)
{
    Super::OnCeaseRelevant(OwnerComp, NodeMemory);
    
    if (!PlayerPawn.Get()) return;

    if (!OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn.Get()))
    OwnerComp.GetAIOwner()->ClearFocus(EAIFocusPriority::Gameplay);
}

UNavigationPath* UTakeConstDistFrom::FindPathInNavMeshFromTarget(UNavigationSystemV1* InNavMesh, FVector TargetLocation, FVector CurrentOwnerLocation, FVector& MoveToTarget)
{
    FVector DirectionToTarget = TargetLocation - CurrentOwnerLocation;
    DirectionToTarget.Normalize();
    
    MoveToTarget = TargetLocation - DirectionToTarget * DistFromTarget;
    return InNavMesh->FindPathToLocationSynchronously(GetWorld(), CurrentOwnerLocation, MoveToTarget);
}

void UTakeConstDistFrom::GoToSmartPointAroundTarget(const UNavigationSystemV1* InNavMesh, AAIController* OwnerController, FVector CurrentOwnerLocation, FVector TargetLocation)
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