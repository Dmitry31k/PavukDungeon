// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServices/BTService_UpdateLastPlayerPos.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdateLastPlayerPos::UBTService_UpdateLastPlayerPos()
{
    NodeName = "Update last known player location";

    bCreateNodeInstance = true;
    bNotifyTick = true;
}

void UBTService_UpdateLastPlayerPos::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
    Super::OnSearchStart(SearchData);

    PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
}

void UBTService_UpdateLastPlayerPos::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if (PlayerPawn.IsValid())
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
    }
}