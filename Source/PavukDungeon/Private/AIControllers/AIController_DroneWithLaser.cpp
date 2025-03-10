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

    if (StartLocation == FirstMoveOffset_AIController)
    {
        return;
    }
    GetBlackboardComponent()->SetValueAsVector(TEXT("FirstMoveOffset"), FirstMoveOffset_AIController);

    if (FirstMoveOffset_AIController == SecondMoveOffset_AIController)
    {
        return;
    }
    GetBlackboardComponent()->SetValueAsVector(TEXT("SecondMoveOffset"), SecondMoveOffset_AIController);

    if (ThirdtMoveOffset_AIController == SecondMoveOffset_AIController)
    {
        return;
    }
    GetBlackboardComponent()->SetValueAsVector(TEXT("ThirdMoveOffset"), ThirdtMoveOffset_AIController);

    if (FourthMoveOffset_AIController == ThirdtMoveOffset_AIController)
    {
        return;
    }
    GetBlackboardComponent()->SetValueAsVector(TEXT("FourthMoveOffset"), FourthMoveOffset_AIController);

    if (FifthMoveOffset_AIController == FourthMoveOffset_AIController)
    {
        return;
    }
    GetBlackboardComponent()->SetValueAsVector(TEXT("FifthMoveOffset"), FifthMoveOffset_AIController);
}