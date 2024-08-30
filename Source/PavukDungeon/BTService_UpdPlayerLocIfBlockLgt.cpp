// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdPlayerLocIfBlockLgt.h"
#include "ShootingDrone.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTService_UpdPlayerLocIfBlockLgt::UBTService_UpdPlayerLocIfBlockLgt()
{
    NodeName = "Update player location if overlap backlight";
}

void UBTService_UpdPlayerLocIfBlockLgt::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AShootingDrone* Drone = Cast<AShootingDrone>(OwnerComp.GetAIOwner()->GetPawn());
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

    if (Drone == nullptr || PlayerPawn == nullptr)
    {
        return;
    }

    UpdatePlayerLocationIfInDroneRangeOfVision(Drone, PlayerPawn);
}

void UBTService_UpdPlayerLocIfBlockLgt::UpdatePlayerLocationIfInDroneRangeOfVision(AShootingDrone* Drone, APawn* PlayerPawn)
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