// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServices/BTService_UpdatePlLocIfShooted.h"
#include "Characters/BaseCharacter.h"
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

    ABaseCharacter* OwnerBaseCharacterPawn = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

    if (OwnerBaseCharacterPawn == nullptr || PlayerPawn == nullptr)
    {
        return;
    }

    UpdatePlayerLocationIfShootedByPlayer(OwnerComp, OwnerBaseCharacterPawn, PlayerPawn);
}

void UBTService_UpdatePlLocIfShooted::UpdatePlayerLocationIfShootedByPlayer(UBehaviorTreeComponent& OwnerComp, class ABaseCharacter* OwnerBaseCharacterPawn, APawn* PlayerPawn)
{
    if (OwnerBaseCharacterPawn->IsWasHitByPlayer)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
        OwnerBaseCharacterPawn->IsWasHitByPlayer = false;
    }
}