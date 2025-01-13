// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllers/AIController_ShooterPavuk.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

void AAIController_ShooterPavuk::BeginPlay()
{
    Super::BeginPlay();

    if (ShooterPavukBehaviorTreeClass)
    {
        RunBehaviorTree(ShooterPavukBehaviorTreeClass);

        APawn* OwnerPawn = GetPawn();

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartShooterPavukLocation"), OwnerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartShooterPavukStartForwardVector"), OwnerPawn->GetActorForwardVector() * 800 + OwnerPawn->GetActorLocation());
    }
}