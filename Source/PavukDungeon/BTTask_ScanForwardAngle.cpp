// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ScanForwardAngle.h"
#include "Math/UnrealMathUtility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTTask_ScanForwardAngle::UBTTask_ScanForwardAngle()
{
    NodeName = "Scan selected forward angle";
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_ScanForwardAngle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerController = OwnerComp.GetAIOwner();
    OwnerPawn = OwnerController->GetPawn();

    if (OwnerController == nullptr || OwnerPawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    else
    {
        StartRotation.Yaw = FRotator::ClampAxis(OwnerPawn->GetActorRotation().Yaw);
        CurrentRotation.Yaw = FRotator::ClampAxis(StartRotation.Yaw);
        TargetRotation.Yaw = FRotator::ClampAxis(StartRotation.Yaw - YawAngleValue / 2);
    }

    return EBTNodeResult::InProgress;
}

void UBTTask_ScanForwardAngle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    if(IsWasScannedFullAngle)
    {
        ReturnToStartPosition(OwnerComp, DeltaSeconds);
    }
    else
    {
        ScanForwardAngle(OwnerComp, DeltaSeconds);
    }    
}

void UBTTask_ScanForwardAngle::ScanForwardAngle(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds)
{
    if (FMath::IsNearlyEqual(CurrentRotation.Yaw, TargetRotation.Yaw))
    {
        if (IsWasTurnRight)
        {
            IsWasScannedFullAngle = true;
        }

        TargetRotation.Yaw = FRotator::ClampAxis(CurrentRotation.Yaw + YawAngleValue);
        IsWasTurnRight = true;
    }
    else
    {
        FRotator RotateTo = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaSeconds, RotationSpeed);
        OwnerPawn->SetActorRotation(RotateTo);

        CurrentRotation.Yaw = FRotator::ClampAxis(OwnerPawn->GetActorRotation().Yaw);
    }
}

void UBTTask_ScanForwardAngle::ReturnToStartPosition(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds)
{
    FRotator RotateTo = FMath::RInterpConstantTo(CurrentRotation, StartRotation, DeltaSeconds, RotationSpeed);
    OwnerPawn->SetActorRotation(RotateTo);

    CurrentRotation.Yaw = FRotator::ClampAxis(OwnerPawn->GetActorRotation().Yaw);

    if (FMath::IsNearlyEqual(CurrentRotation.Yaw, StartRotation.Yaw))
    {
        IsWasTurnRight = false;
        IsWasScannedFullAngle = false;

        StartRotation.Yaw = FRotator::ClampAxis(OwnerPawn->GetActorRotation().Yaw);
        CurrentRotation.Yaw = FRotator::ClampAxis(StartRotation.Yaw);
        TargetRotation.Yaw = FRotator::ClampAxis(StartRotation.Yaw - YawAngleValue / 2);

        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}
