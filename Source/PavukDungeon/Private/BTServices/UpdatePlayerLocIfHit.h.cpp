// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServices/UpdatePlayerLocIfHit.h"
#include "Interfaces/EnemyInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTreeTypes.h"

UUpdatePlayerLocIfHit::UUpdatePlayerLocIfHit()
{
    NodeName = "Get player location if player hit";

    bNotifyBecomeRelevant = true;
    bNotifyCeaseRelevant = true;
}

uint16 UUpdatePlayerLocIfHit::GetSpecialMemorySize() const
{
    return sizeof(FBTUpdatePlayerLocIfHitMemory);
}

void UUpdatePlayerLocIfHit::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::OnBecomeRelevant(OwnerComp, NodeMemory);

    FBTUpdatePlayerLocIfHitMemory* MyNodeMemory = GetSpecialNodeMemory<FBTUpdatePlayerLocIfHitMemory>(NodeMemory);

    if (IEnemyInterface* Enemy = Cast<IEnemyInterface>(OwnerComp.GetAIOwner()))
    {
        TWeakObjectPtr<UBehaviorTreeComponent> OwnerCompPtr = &OwnerComp;
        MyNodeMemory->BoundLambdaHandle = Enemy->GetOnHitByPlayer().AddLambda([this, OwnerCompPtr](AActor* DetectedPlayer, AAIController* DetectingController)
        {
            if (OwnerCompPtr.Get() && DetectedPlayer)
            {
                OwnerCompPtr.Get()->GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), DetectedPlayer->GetActorLocation());
            }
        });
    }
}

void UUpdatePlayerLocIfHit::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::OnCeaseRelevant(OwnerComp, NodeMemory);

    FBTUpdatePlayerLocIfHitMemory* MyNodeMemory = GetSpecialNodeMemory<FBTUpdatePlayerLocIfHitMemory>(NodeMemory);

    if (!MyNodeMemory->BoundLambdaHandle.IsValid())
    return;

    if (IEnemyInterface* Enemy = Cast<IEnemyInterface>(OwnerComp.GetAIOwner()))
    {
        Enemy->GetOnHitByPlayer().Remove(MyNodeMemory->BoundLambdaHandle);
        MyNodeMemory->BoundLambdaHandle.Reset();
    }
}