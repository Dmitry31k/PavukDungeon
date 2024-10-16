// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/BTTask_SmoothRotateTo.h"
#include "Math/UnrealMathUtility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTTask_SmoothRotateTo::UBTTask_SmoothRotateTo()
{
    NodeName = "Smooth rotate to selected location";
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_SmoothRotateTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerController = OwnerComp.GetAIOwner();
    OwnerPawn = OwnerController->GetPawn();

    if (OwnerController == nullptr || OwnerPawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    return EBTNodeResult::InProgress;
}

void UBTTask_SmoothRotateTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    SmoothRotate(OwnerComp, DeltaSeconds);
}

void UBTTask_SmoothRotateTo::SmoothRotate(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds)
{
    CurrentRotation = OwnerPawn->GetActorRotation();
    TargetRotation = (OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey()) - OwnerPawn->GetActorLocation()).Rotation();

    FRotator RotateTo = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaSeconds, RotationSpeed);

    OwnerPawn->SetActorRotation(FRotator (0.f, RotateTo.Yaw, 0.f));

    if (FMath::IsNearlyEqual(CurrentRotation.Yaw, TargetRotation.Yaw))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}