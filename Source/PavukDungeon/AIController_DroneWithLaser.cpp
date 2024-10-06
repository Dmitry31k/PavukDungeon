// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_DroneWithLaser.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"

void AAIController_DroneWithLaser::BeginPlay()
{
    Super::BeginPlay();
    
    if (DroneWithLaserBehaviorTreeClass)
    {
        UBehaviorTree* PersonalBehaviorTree = DuplicateObject<UBehaviorTree>(DroneWithLaserBehaviorTreeClass, this);

        if (PersonalBehaviorTree)
        {
            RunBehaviorTree(PersonalBehaviorTree);

            GetBlackboardComponent()->SetValueAsVector(TEXT("StartDroneLocation"), GetPawn()->GetActorLocation());
            GetBlackboardComponent()->SetValueAsVector(TEXT("StartDroneForwardVector"), GetPawn()->GetActorForwardVector());
        
            GetWorldTimerManager().SetTimer(SetVariablesTimer, this, &AAIController_DroneWithLaser::SetVariabledIntoBlackboard, 0.5, false);
        }        
    }
}

void AAIController_DroneWithLaser::SetVariabledIntoBlackboard()
{
    GetBlackboardComponent()->SetValueAsVector(TEXT("FirstMoveOffset"), FirstMoveOffset_AIController);
    GetBlackboardComponent()->SetValueAsVector(TEXT("SecondMoveOffset"), SecondMoveOffset_AIController);
    GetBlackboardComponent()->SetValueAsVector(TEXT("ThirdMoveOffset"), ThirdtMoveOffset_AIController);
    GetBlackboardComponent()->SetValueAsVector(TEXT("FourthMoveOffset"), FourthMoveOffset_AIController);
    GetBlackboardComponent()->SetValueAsVector(TEXT("FifthMoveOffset"), FifthMoveOffset_AIController);
    GetBlackboardComponent()->SetValueAsBool(TEXT("MustRotating"), MustRotating_AIController);
    GetBlackboardComponent()->SetValueAsBool(TEXT("MustMoving"), MustMoving_AIController);
    GetBlackboardComponent()->SetValueAsBool(TEXT("MustRotatingAndMoving"), MustRotatingAndMoving_AIController);
}