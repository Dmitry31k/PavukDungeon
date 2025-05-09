// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/BTTask_MoveToWithoutRotation.h"
#include "Math/UnrealMathUtility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

uint16 UBTTask_MoveToWithoutRotation::GetInstanceMemorySize() const
{
    return sizeof(FBTMoveToWithoutRotationNodeMemory);
}

UBTTask_MoveToWithoutRotation::UBTTask_MoveToWithoutRotation()
{
    NodeName = "Move to target without changing rotation";
    bNotifyTick = true;
    bCreateNodeInstance = true;
    bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_MoveToWithoutRotation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    FBTMoveToWithoutRotationNodeMemory* MyNodeMemory = reinterpret_cast<FBTMoveToWithoutRotationNodeMemory*>(NodeMemory);

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

    FBTMoveToWithoutRotationNodeMemory* MyNodeMemory = reinterpret_cast<FBTMoveToWithoutRotationNodeMemory*>(NodeMemory);

    SmoothMoveToTargetWithoutRotation(DeltaSeconds, OwnerComp, MyNodeMemory);
}

void UBTTask_MoveToWithoutRotation::SmoothMoveToTargetWithoutRotation(float DeltaSeconds, UBehaviorTreeComponent& OwnerComp, FBTMoveToWithoutRotationNodeMemory* MyNodeMemory)
{
    MyNodeMemory->CurrentLocation = OwnerPawn->GetActorLocation();
    MyNodeMemory->TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

    FVector ToSetLocation = FMath::VInterpConstantTo(
        MyNodeMemory->CurrentLocation, 
        MyNodeMemory->TargetLocation,
        DeltaSeconds,
        MovingSpeed
    );

    if (FVector::Dist(MyNodeMemory->CurrentLocation, MyNodeMemory->TargetLocation) <= 1)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }

    OwnerPawn->SetActorLocation(ToSetLocation);
}