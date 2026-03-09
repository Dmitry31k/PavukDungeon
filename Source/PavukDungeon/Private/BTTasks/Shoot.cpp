// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/Shoot.h"
#include "Characters/BaseCharacter.h"
#include "AIController.h"

UShoot::UShoot()
{
    NodeName = "Shoot";
}

EBTNodeResult::Type UShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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