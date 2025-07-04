// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/BTTask_ShootD.h"
#include "Characters/BaseCharacter.h"
#include "AIController.h"

UBTTask_ShootD::UBTTask_ShootD()
{
    NodeName = "Shoot";
}

EBTNodeResult::Type UBTTask_ShootD::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    ABaseCharacter* Character = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    if (Character == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    Character->Shoot();

    return EBTNodeResult::Succeeded;
}