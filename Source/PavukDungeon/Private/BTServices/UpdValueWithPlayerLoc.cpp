// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServices/UpdValueWithPlayerLoc.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UUpdValueWithPlayerLoc::UUpdValueWithPlayerLoc()
{
    NodeName = "Update selected blackboard key with value";

    bNotifyTick = true;
}

void UUpdValueWithPlayerLoc::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    FVector PlayerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(PlayerLocationValueName);

    if (!OwnerComp.GetBlackboardComponent()->IsVectorValueSet(PlayerLocationValueName))
    return;

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);
}