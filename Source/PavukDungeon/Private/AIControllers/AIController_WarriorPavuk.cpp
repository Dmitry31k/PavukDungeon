// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllers/AIController_WarriorPavuk.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

void AAIController_WarriorPavuk::BeginPlay()
{
    Super::BeginPlay();

    if (WarriorPavukBehaviorTreeClass)
    {
        RunBehaviorTree(WarriorPavukBehaviorTreeClass);

        APawn* OwnerPawn = GetPawn();

        GetBlackboardComponent()->SetValueAsVector(TEXT("WarriorPavukStartLocation"), OwnerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("WarriorPavukStartForwardVector"), OwnerPawn->GetActorForwardVector() * 800 + OwnerPawn->GetActorLocation());
    }
}