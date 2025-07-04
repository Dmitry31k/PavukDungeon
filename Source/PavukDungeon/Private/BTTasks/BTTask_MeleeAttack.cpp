// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/BTTask_MeleeAttack.h"
#include "AIController.h"
#include "Characters/BaseCharacter.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
    NodeName = "Melee attack";
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    ABaseCharacter* Character = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    if (Character == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    Character->MeleeAttack();

    return EBTNodeResult::Succeeded;
}