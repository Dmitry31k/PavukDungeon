// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServices/UpdPlayerLocIfOverlaps.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"

UUpdPlayerLocIfOverlaps::UUpdPlayerLocIfOverlaps()
{
    NodeName = "Update player location if overlap owner";

    bNotifyBecomeRelevant = true;
    bNotifyCeaseRelevant = true;
}

uint16 UUpdPlayerLocIfOverlaps::GetSpecialMemorySize() const
{
    return sizeof(FBTUpdPlayerLocIfOverlapsMemory);
}

void UUpdPlayerLocIfOverlaps::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::OnBecomeRelevant(OwnerComp, NodeMemory);

    FBTUpdPlayerLocIfOverlapsMemory* MyNodeMemory = GetSpecialNodeMemory<FBTUpdPlayerLocIfOverlapsMemory>(NodeMemory);
    AAIController* OwnerController = OwnerComp.GetAIOwner();
    TargetPlayer = UGameplayStatics::GetPlayerPawn(this, 0);

    InitLambdasToDelegats(OwnerController, MyNodeMemory);
}

void UUpdPlayerLocIfOverlaps::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if (!TargetPlayer.Get())
    {
        TargetPlayer = UGameplayStatics::GetPlayerPawn(this, 0);
        return;
    }

    FBTUpdPlayerLocIfOverlapsMemory* MyNodeMemory = GetSpecialNodeMemory<FBTUpdPlayerLocIfOverlapsMemory>(NodeMemory);

    if (MyNodeMemory->bCanSeePlayer)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TargetPlayer->GetActorLocation());
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}

void UUpdPlayerLocIfOverlaps::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::OnCeaseRelevant(OwnerComp, NodeMemory);

    FBTUpdPlayerLocIfOverlapsMemory* MyNodeMemory = GetSpecialNodeMemory<FBTUpdPlayerLocIfOverlapsMemory>(NodeMemory);

    if (IEnemyInterface* Enemy = Cast<IEnemyInterface>(OwnerComp.GetAIOwner()))
    {
        for (auto Pair : MyNodeMemory->LambdasToDelegats)
        {
            if (Pair.Key.IsValid())
            {
                Pair.Value->Remove(Pair.Key);
                Pair.Key.Reset();
            }
        }
        MyNodeMemory->LambdasToDelegats.Reset();
    }
}

void UUpdPlayerLocIfOverlaps::InitLambdasToDelegats(AAIController* OwnerController, FBTUpdPlayerLocIfOverlapsMemory* NodeMemory)
{
    if (IEnemyInterface* Enemy = Cast<IEnemyInterface>(OwnerController))
    {
        FDelegateHandle StartOverlapDelegateHandle = Enemy->GetOnPlayerStartOverlapVision().AddLambda(
            [NodeMemory](AActor* OverlappedPlayer, AAIController* DetectingController)
            {
                NodeMemory->bCanSeePlayer = true;
            }
        );
        FDelegateHandle EndOverlapDelegateHandle = Enemy->GetOnPlayerEndOverlapVision().AddLambda(
            [NodeMemory](AActor* OverlappedPlayer, AAIController* DetectingController)
            {
                NodeMemory->bCanSeePlayer = false;
            }    
        );

        NodeMemory->LambdasToDelegats.Add(StartOverlapDelegateHandle, &Enemy->GetOnPlayerStartOverlapVision());
        NodeMemory->LambdasToDelegats.Add(EndOverlapDelegateHandle, &Enemy->GetOnPlayerEndOverlapVision());
    }
}