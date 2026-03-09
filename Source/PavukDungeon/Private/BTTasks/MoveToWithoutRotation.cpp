// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/MoveToWithoutRotation.h"
#include "Math/UnrealMathUtility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UMoveToWithoutRotation::UMoveToWithoutRotation()
{
    NodeName = "Move to target without changing rotation";
    bNotifyTick = true;
    bNotifyTaskFinished = true;
}

EBTNodeResult::Type UMoveToWithoutRotation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    return EBTNodeResult::InProgress;
}

void UMoveToWithoutRotation::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    SmoothMoveToTargetWithoutRotation(DeltaSeconds, OwnerComp);
}

void UMoveToWithoutRotation::SmoothMoveToTargetWithoutRotation(float DeltaSeconds, UBehaviorTreeComponent& OwnerComp)
{
    APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();

    FVector CurrentLocation = OwnerPawn->GetActorLocation();
    FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

    FVector ToSetLocation = FMath::VInterpConstantTo(
        CurrentLocation, 
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