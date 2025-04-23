// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServices/BTService_UpdPlayerLocIfBlockLgt.h"
#include "Characters/Drones/ShootingDrone.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"

UBTService_UpdPlayerLocIfBlockLgt::UBTService_UpdPlayerLocIfBlockLgt()
{
    NodeName = "Update player location if overlap backlight";

    bCreateNodeInstance = true;
    bNotifyTick = true;
}

void UBTService_UpdPlayerLocIfBlockLgt::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
    Super::OnSearchStart(SearchData);

    Drone = Cast<AShootingDrone>(SearchData.OwnerComp.GetAIOwner()->GetPawn());
    PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

    if (Drone == nullptr)
    {
        return;
    }
}

void UBTService_UpdPlayerLocIfBlockLgt::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if (PlayerPawn == nullptr)
    {
        return;
    }

    UpdatePlayerLocationIfInDroneRangeOfVision(OwnerComp);
}

void UBTService_UpdPlayerLocIfBlockLgt::UpdatePlayerLocationIfInDroneRangeOfVision(UBehaviorTreeComponent& OwnerComp)
{
    if (Drone->IsDroneLineOfSightOverlappedByPlayer == true)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}