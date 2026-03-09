// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/MeleeAttack.h"
#include "AIController.h"
#include "Characters/BaseCharacter.h"

UMeleeAttack::UMeleeAttack()
{
    NodeName = "Melee attack";
}

EBTNodeResult::Type UMeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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