// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServices/BTService_UpdatePlLocIfShooted.h"
#include "Characters/BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTreeTypes.h"

UBTService_UpdatePlLocIfShooted::UBTService_UpdatePlLocIfShooted()
{
    NodeName = "Get player location if player hit";

    bCreateNodeInstance = true;
    bNotifyTick = true;
}

void UBTService_UpdatePlLocIfShooted::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
    Super::OnSearchStart(SearchData);

    if (OwnerPawn == nullptr || PlayerPawn == nullptr)
    {
        OwnerPawn = Cast<ABaseCharacter>(SearchData.OwnerComp.GetAIOwner()->GetPawn());
        PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    }
}

void UBTService_UpdatePlLocIfShooted::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    UpdatePlayerLocationIfShootedByPlayer(OwnerComp);
}

void UBTService_UpdatePlLocIfShooted::UpdatePlayerLocationIfShootedByPlayer(UBehaviorTreeComponent& OwnerComp)
{
    if (OwnerPawn->IsWasHitByPlayer)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
        OwnerPawn->IsWasHitByPlayer = false;
    }
}