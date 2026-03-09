// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UClearBlackboardValue::UClearBlackboardValue()
{
    NodeName = "Clear blackboard value";
}

EBTNodeResult::Type UClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

    return EBTNodeResult::Succeeded;
}