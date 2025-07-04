// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/BTTask_MoveToWithConstDist.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"

UBTTask_MoveToWithConstDist::UBTTask_MoveToWithConstDist()
{
    NodeName = "Move to target with const distance";
}

EBTNodeResult::Type UBTTask_MoveToWithConstDist::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerController = OwnerComp.GetAIOwner();
    OwnerPawn = OwnerController->GetPawn();

    if (OwnerPawn == nullptr || OwnerController == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
    FVector Direction = (TargetLocation - OwnerPawn->GetActorLocation()).GetSafeNormal();
    FVector MoveToTarget = TargetLocation - Direction * DistFromTarget;

    OwnerController->MoveTo(MoveToTarget);

    return EBTNodeResult::Succeeded;
}