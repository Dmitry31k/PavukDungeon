// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Drone.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void AAIController_Drone::BeginPlay()
{
    Super::BeginPlay();

    if (DroneBehaviorTree)
    {
        RunBehaviorTree(DroneBehaviorTree);

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartDroneLocation"), GetPawn()->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartDroneForwardVector"), GetPawn()->GetActorForwardVector() + GetPawn()->GetActorLocation());
    }
}