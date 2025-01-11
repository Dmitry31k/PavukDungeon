// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/BTTask_SmoothRotateTo.h"
#include "Math/UnrealMathUtility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTTask_SmoothRotateTo::UBTTask_SmoothRotateTo()
{
    NodeName = "Smooth rotate to selected location";
    bNotifyTick = true;
    bNotifyTaskFinished = true;
    bCreateNodeInstance = true;
}

uint16 UBTTask_SmoothRotateTo::GetInstanceMemorySize() const
{
    return sizeof(FBTSmoothRotateToNodeMemory);
}

EBTNodeResult::Type UBTTask_SmoothRotateTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    FBTSmoothRotateToNodeMemory* MyNodeMemory = reinterpret_cast<FBTSmoothRotateToNodeMemory*>(NodeMemory);

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

    FBTSmoothRotateToNodeMemory* MyNodeMemory = reinterpret_cast<FBTSmoothRotateToNodeMemory*>(NodeMemory);

    SmoothRotate(OwnerComp, DeltaSeconds, MyNodeMemory);
}

void UBTTask_SmoothRotateTo::SmoothRotate(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds, FBTSmoothRotateToNodeMemory* MyNodeMemory)
{
    MyNodeMemory->CurrentRotation = OwnerPawn->GetActorRotation();
    MyNodeMemory->TargetRotation = (OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey()) - OwnerPawn->GetActorLocation()).Rotation();

    FRotator RotateTo = FMath::RInterpConstantTo(MyNodeMemory->CurrentRotation, MyNodeMemory->TargetRotation, DeltaSeconds, RotationSpeed);

    OwnerPawn->SetActorRotation(FRotator (0.f, RotateTo.Yaw, 0.f));

    if (FMath::IsNearlyEqual(MyNodeMemory->CurrentRotation.Yaw, MyNodeMemory->TargetRotation.Yaw))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}