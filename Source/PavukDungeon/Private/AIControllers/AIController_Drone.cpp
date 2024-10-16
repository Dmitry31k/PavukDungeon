// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllers/AIController_Drone.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BehaviorTree.h"

void AAIController_Drone::BeginPlay()
{
    Super::BeginPlay();

    if (DroneBehaviorTreeClass)
    {
        UBehaviorTree* PersonalBehaviorTree = DuplicateObject<UBehaviorTree>(DroneBehaviorTreeClass, this);

        RunBehaviorTree(PersonalBehaviorTree);

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartDroneLocation"), GetPawn()->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartDroneForwardVector"), GetPawn()->GetActorForwardVector() + GetPawn()->GetActorLocation());
    }
}