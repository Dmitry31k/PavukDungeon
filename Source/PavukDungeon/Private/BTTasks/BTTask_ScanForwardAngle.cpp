// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/BTTask_ScanForwardAngle.h"
#include "Math/UnrealMathUtility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

uint16 UBTTask_ScanForwardAngle::GetInstanceMemorySize() const
{
    return sizeof(FBTScanForwardAngleNodeMemory);
}

UBTTask_ScanForwardAngle::UBTTask_ScanForwardAngle()
{
    NodeName = "Scan selected forward angle";
    bNotifyTick = true;
    bNotifyTaskFinished = true;
    bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_ScanForwardAngle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    FBTScanForwardAngleNodeMemory* MyNodeMemory = reinterpret_cast<FBTScanForwardAngleNodeMemory*>(NodeMemory);

    OwnerController = OwnerComp.GetAIOwner();
    OwnerPawn = OwnerController->GetPawn();

    if (OwnerController == nullptr || OwnerPawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    else
    {
        MyNodeMemory->StartRotation.Yaw = FRotator::ClampAxis(OwnerPawn->GetActorRotation().Yaw);
        MyNodeMemory->CurrentRotation.Yaw = FRotator::ClampAxis(MyNodeMemory->StartRotation.Yaw);
        MyNodeMemory->TargetRotation.Yaw = FRotator::ClampAxis(MyNodeMemory->StartRotation.Yaw - YawAngleValue / 2);
    }

    return EBTNodeResult::InProgress;
}

void UBTTask_ScanForwardAngle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    FBTScanForwardAngleNodeMemory* MyNodeMemory = reinterpret_cast<FBTScanForwardAngleNodeMemory*>(NodeMemory);

    if(MyNodeMemory->IsWasScannedFullAngle)
    {
        ReturnToStartPosition(OwnerComp, DeltaSeconds, MyNodeMemory);
    }
    else
    {
        ScanForwardAngle(OwnerComp, DeltaSeconds, MyNodeMemory);
    }    
}

void UBTTask_ScanForwardAngle::ScanForwardAngle(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds, FBTScanForwardAngleNodeMemory* MyNodeMemory)
{
    if (FMath::IsNearlyEqual(MyNodeMemory->CurrentRotation.Yaw, MyNodeMemory->TargetRotation.Yaw))
    {
        if (MyNodeMemory->IsWasTurnRight)
        {
            MyNodeMemory->IsWasScannedFullAngle = true;
        }

        MyNodeMemory->TargetRotation.Yaw = FRotator::ClampAxis(MyNodeMemory->CurrentRotation.Yaw + YawAngleValue);
        MyNodeMemory->IsWasTurnRight = true;
    }
    else
    {
        FRotator RotateTo = FMath::RInterpConstantTo(MyNodeMemory->CurrentRotation, MyNodeMemory->TargetRotation, DeltaSeconds, RotationSpeed);
        OwnerPawn->SetActorRotation(RotateTo);

        MyNodeMemory->CurrentRotation.Yaw = FRotator::ClampAxis(OwnerPawn->GetActorRotation().Yaw);
    }
}

void UBTTask_ScanForwardAngle::ReturnToStartPosition(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds, FBTScanForwardAngleNodeMemory* MyNodeMemory)
{
    FRotator RotateTo = FMath::RInterpConstantTo(MyNodeMemory->CurrentRotation, MyNodeMemory->StartRotation, DeltaSeconds, RotationSpeed);
    OwnerPawn->SetActorRotation(RotateTo);

    MyNodeMemory->CurrentRotation.Yaw = FRotator::ClampAxis(OwnerPawn->GetActorRotation().Yaw);

    if (FMath::IsNearlyEqual(MyNodeMemory->CurrentRotation.Yaw, MyNodeMemory->StartRotation.Yaw))
    {
        MyNodeMemory->IsWasTurnRight = false;
        MyNodeMemory->IsWasScannedFullAngle = false;

        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}