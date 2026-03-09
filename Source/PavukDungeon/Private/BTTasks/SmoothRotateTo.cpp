// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/SmoothRotateTo.h"
#include "Math/UnrealMathUtility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

USmoothRotateTo::USmoothRotateTo()
{
    NodeName = "Smooth rotate to selected location";
    bNotifyTick = true;
}

EBTNodeResult::Type USmoothRotateTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    return EBTNodeResult::InProgress;
}

void USmoothRotateTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    SmoothRotate(OwnerComp, DeltaSeconds);
}

void USmoothRotateTo::SmoothRotate(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds)
{
    APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
    FRotator CurrentRotation = OwnerPawn->GetActorRotation();

    FRotator TargetRotation = (OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey()) - OwnerPawn->GetActorLocation()).Rotation();
    FRotator RotateTo = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaSeconds, RotationSpeed);

    OwnerPawn->SetActorRotation(FRotator (0.f, RotateTo.Yaw, 0.f));

    if (FMath::IsNearlyEqual(RotateTo.Yaw, TargetRotation.Yaw))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}