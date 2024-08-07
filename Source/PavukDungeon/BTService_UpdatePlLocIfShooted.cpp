// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlLocIfShooted.h"
#include "ShootingDrone.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

UBTService_UpdatePlLocIfShooted::UBTService_UpdatePlLocIfShooted()
{
    NodeName = "Get player location if player hit";
}

void UBTService_UpdatePlLocIfShooted::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AShootingDrone* Drone = Cast<AShootingDrone>(OwnerComp.GetAIOwner()->GetPawn());
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

    if (Drone == nullptr || PlayerPawn == nullptr)
    {
        return;
    }

    if (Drone->IsWasShotedByPlayer)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
        Drone->IsWasShotedByPlayer = false;
    }
} 