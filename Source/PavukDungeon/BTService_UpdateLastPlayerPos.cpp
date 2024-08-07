// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateLastPlayerPos.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdateLastPlayerPos::UBTService_UpdateLastPlayerPos()
{
    NodeName = "Update last known player location";
}

void UBTService_UpdateLastPlayerPos::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

    if (PlayerPawn)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
    }
}