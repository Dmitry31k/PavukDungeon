// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_DroneWithLaser.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DroneWithLaser.h"

void AAIController_DroneWithLaser::BeginPlay()
{
    Super::BeginPlay();

    if (DroneWithLaserBehaviorTree)
    {
        RunBehaviorTree(DroneWithLaserBehaviorTree);

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartDroneLocation"), GetPawn()->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartDroneForwardVector"), GetPawn()->GetActorForwardVector());

        ADroneWithLaser* Drone = Cast<ADroneWithLaser>(GetOwner());

        if (Drone)
        {
            GetBlackboardComponent()->SetValueAsVector(TEXT("FirstMoveOffset"), Drone->FirstMoveOffset);
            GetBlackboardComponent()->SetValueAsVector(TEXT("SecondMoveOffset"), Drone->SecondMoveOffset);
            GetBlackboardComponent()->SetValueAsVector(TEXT("ThirdMoveOffset"), Drone->ThirdtMoveOffset);
            GetBlackboardComponent()->SetValueAsVector(TEXT("FourthMoveOffset"), Drone->FourthMoveOffset);
            GetBlackboardComponent()->SetValueAsVector(TEXT("FifthMoveOffset"), Drone->FifthMoveOffset);
        }
    }
}