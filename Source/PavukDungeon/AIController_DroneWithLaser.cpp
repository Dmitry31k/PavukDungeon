// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_DroneWithLaser.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AAIController_DroneWithLaser::BeginPlay()
{
    Super::BeginPlay();

    if (DroneWithLaserBehaviorTree)
    {
        RunBehaviorTree(DroneWithLaserBehaviorTree);

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartDroneLocation"), GetPawn()->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartDroneForwardVector"), GetPawn()->GetActorForwardVector());
    }
}