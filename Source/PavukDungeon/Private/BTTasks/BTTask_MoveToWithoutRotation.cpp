// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/BTTask_MoveToWithoutRotation.h"
#include "Math/UnrealMathUtility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTTask_MoveToWithoutRotation::UBTTask_MoveToWithoutRotation()
{
    NodeName = "Move to target without changing rotation";
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MoveToWithoutRotation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerAIController = OwnerComp.GetAIOwner();
    OwnerPawn = OwnerAIController->GetPawn();

    if (OwnerPawn == nullptr || OwnerAIController == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    return EBTNodeResult::InProgress;
}

void UBTTask_MoveToWithoutRotation::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    FVector CurrentLocation = OwnerPawn->GetActorLocation();
    FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

    FVector ToSetLocation = FMath::VInterpConstantTo(CurrentLocation, 
        TargetLocation,
        DeltaSeconds,
        MovingSpeed
    );

    if (FVector::Dist(CurrentLocation, TargetLocation) <= 1)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }

    OwnerPawn->SetActorLocation(ToSetLocation);
}