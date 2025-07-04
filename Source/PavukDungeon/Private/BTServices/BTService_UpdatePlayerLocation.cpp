// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServices/BTService_UpdatePlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation()
{
    NodeName = "Update location if see player";
}

void UBTService_UpdatePlayerLocation::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
    Super::OnSearchStart(SearchData);

    if (PlayerPawn == nullptr || AIOwnerController == nullptr)
    {
        PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
        AIOwnerController = SearchData.OwnerComp.GetAIOwner();
    }
}

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if (AIOwnerController->LineOfSightTo(PlayerPawn.Get()))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}