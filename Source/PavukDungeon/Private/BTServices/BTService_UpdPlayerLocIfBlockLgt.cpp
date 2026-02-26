// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServices/BTService_UpdPlayerLocIfBlockLgt.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Interfaces/EnemyVisionInterface.h"

UBTService_UpdPlayerLocIfBlockLgt::UBTService_UpdPlayerLocIfBlockLgt()
{
    NodeName = "Update player location if overlap backlight";

    bCreateNodeInstance = true;
    bNotifyTick = true;
}

void UBTService_UpdPlayerLocIfBlockLgt::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
    Super::OnSearchStart(SearchData);

    if (!EnemyOwner)
    {
        APawn* OwnerPawn = SearchData.OwnerComp.GetAIOwner()->GetPawn();

        if (OwnerPawn->Implements<UEnemyVisionInterface>())
        {
            EnemyOwner = OwnerPawn;
        }
    }
}

void UBTService_UpdPlayerLocIfBlockLgt::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    UpdatePlayerLocationIfInDroneRangeOfVision(OwnerComp);
}

void UBTService_UpdPlayerLocIfBlockLgt::UpdatePlayerLocationIfInDroneRangeOfVision(UBehaviorTreeComponent& OwnerComp)
{
    if (!EnemyOwner)
    return;

    if (EnemyOwner->CanEnemySeePlayer())
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), EnemyOwner->GetPlayerLocation());
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}