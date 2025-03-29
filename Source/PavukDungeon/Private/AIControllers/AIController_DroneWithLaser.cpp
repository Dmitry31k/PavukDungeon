// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllers/AIController_DroneWithLaser.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

void AAIController_DroneWithLaser::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (DroneWithLaserBehaviorTreeClass)
    {
        RunBehaviorTree(DroneWithLaserBehaviorTreeClass);

        APawn* OwnerPawn = GetPawn();
        StartLocation = OwnerPawn->GetActorLocation();

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartDroneLocation"), StartLocation);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartDroneForwardVector"), StartLocation + OwnerPawn->GetActorForwardVector() * 8);
        
        GetWorldTimerManager().SetTimer(SetVariablesTimer, this, &AAIController_DroneWithLaser::SetVariabledIntoBlackboard, 0.25, false);
    }
}

void AAIController_DroneWithLaser::SetVariabledIntoBlackboard()
{
    GetBlackboardComponent()->SetValueAsBool(TEXT("MustRotating"), MustRotating_AIController);
    GetBlackboardComponent()->SetValueAsBool(TEXT("MustMoving"), MustMoving_AIController);
    GetBlackboardComponent()->SetValueAsBool(TEXT("MustRotatingAndMoving"), MustRotatingAndMoving_AIController);

    TArray<OffsetData> OffsetArray = {
        {"FirstMoveOffset", FirstMoveOffset_AIController, StartLocation},
        {"SecondMoveOffset", SecondMoveOffset_AIController, FirstMoveOffset_AIController},
        {"ThirdMoveOffset", ThirdtMoveOffset_AIController, SecondMoveOffset_AIController},
        {"FourthMoveOffset", FourthMoveOffset_AIController, ThirdtMoveOffset_AIController},
        {"FifthMoveOffset", FifthMoveOffset_AIController, FourthMoveOffset_AIController}
    };

    for (const auto& Offset : OffsetArray)
    {
        if (Offset.CurrentValue != Offset.PreviousValue)
        {
            GetBlackboardComponent()->SetValueAsVector(*Offset.Key, Offset.CurrentValue);
        }
    }
    
}