// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllers/AIController_SummonerPavuk.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

void AAIController_SummonerPavuk::BeginPlay()
{
    Super::BeginPlay();

    if (SummonerPavukBehaviorTreeClass)
    {
        RunBehaviorTree(SummonerPavukBehaviorTreeClass);

        APawn* OwnerPawn = GetPawn();

        GetBlackboardComponent()->SetValueAsVector(TEXT("SummonerPavukStartLocation"), OwnerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("SummonerPavukStartForwardVector"), OwnerPawn->GetActorForwardVector() * 800 + OwnerPawn->GetActorLocation());
    }
}