// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllers/AIController_Drone.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

void AAIController_Drone::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (DroneBehaviorTreeClass)
    {
        RunBehaviorTree(DroneBehaviorTreeClass);

        APawn* OwnerPawn = GetPawn();

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartDroneLocation"), OwnerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartDroneForwardVector"), OwnerPawn->GetActorForwardVector() * 800 + OwnerPawn->GetActorLocation());
    }
}