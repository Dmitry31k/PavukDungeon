// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ShootD.h"
#include "BaseDrone.h"
#include "AIController.h"

UBTTask_ShootD::UBTTask_ShootD()
{
    NodeName = "Drone shooting";
}

EBTNodeResult::Type UBTTask_ShootD::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    ABaseDrone* Drone = Cast<ABaseDrone>(OwnerComp.GetAIOwner()->GetPawn());

    if (Drone == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    Drone->Shoot();

    return EBTNodeResult::Succeeded;
}