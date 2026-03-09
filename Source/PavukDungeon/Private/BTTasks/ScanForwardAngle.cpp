// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/ScanForwardAngle.h"
#include "Math/UnrealMathUtility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UScanForwardAngle::UScanForwardAngle()
{
    NodeName = "Scan selected forward angle";
    bNotifyTick = true;
}

uint16 UScanForwardAngle::GetSpecialMemorySize() const
{
    return sizeof(FBTScanForwardAngleNodeMemory);
}

EBTNodeResult::Type UScanForwardAngle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    FBTScanForwardAngleNodeMemory* MyNodeMemory = GetSpecialNodeMemory<FBTScanForwardAngleNodeMemory>(NodeMemory);
    ResetMemoryParams(MyNodeMemory);

    APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();

    MyNodeMemory->TargetRightRotationYaw = OwnerPawn->GetActorRotation().Yaw + YawAngleToScan / 2;
    MyNodeMemory->TargetLeftRotationYaw = OwnerPawn->GetActorRotation().Yaw - YawAngleToScan / 2;
    MyNodeMemory->StartRotationYaw = OwnerPawn->GetActorRotation().Yaw;

    return EBTNodeResult::InProgress;
}

void UScanForwardAngle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    FBTScanForwardAngleNodeMemory* MyNodeMemory = GetSpecialNodeMemory<FBTScanForwardAngleNodeMemory>(NodeMemory);
    APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();

    FRotator CurrentRotation = OwnerPawn->GetActorRotation();
    FRotator TargetRotation = CurrentRotation;
    
    TargetRotation.Yaw = ChooseTargetRotation(MyNodeMemory);

    FRotator RotateTo = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaSeconds, RotationSpeed);
    OwnerPawn->SetActorRotation(RotateTo);

    if (RotateTo.Equals(TargetRotation, 1.f))
    {
        SwitchToNextRotationStateOrFinish(OwnerComp, MyNodeMemory);
    }
}

float UScanForwardAngle::ChooseTargetRotation(FBTScanForwardAngleNodeMemory* NodeMemory)
{
    switch (NodeMemory->RotationState)
    {
        case ERotationState::RotateToRight:
        return NodeMemory->TargetRightRotationYaw;

        case ERotationState::RotateToLeft:
        return NodeMemory->TargetLeftRotationYaw;

        case ERotationState::RotateToStartPosition:
        return NodeMemory->StartRotationYaw;
    }

    return 0;
}

void UScanForwardAngle::SwitchToNextRotationStateOrFinish(UBehaviorTreeComponent& OwnerComp, FBTScanForwardAngleNodeMemory* NodeMemory)
{
    switch (NodeMemory->RotationState)
    {
        case ERotationState::RotateToRight:

        NodeMemory->RotationState = ERotationState::RotateToLeft;
        break;

        case ERotationState::RotateToLeft:

        NodeMemory->RotationState = ERotationState::RotateToStartPosition;
        break;

        case ERotationState::RotateToStartPosition:

        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        break;
    }
}

void UScanForwardAngle::ResetMemoryParams(FBTScanForwardAngleNodeMemory* NodeMemory)
{
    NodeMemory->TargetLeftRotationYaw = 0.f;
    NodeMemory->TargetRightRotationYaw = 0.f;
    NodeMemory->StartRotationYaw = 0.f;
    
    NodeMemory->RotationState = ERotationState::RotateToRight;
}