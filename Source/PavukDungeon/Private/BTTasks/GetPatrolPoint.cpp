// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/GetPatrolPoint.h"
#include "Interfaces/EnemyInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

uint16 UGetPatrolPoint::GetSpecialMemorySize() const
{
    return sizeof(FBTGetPatrolPointMemory);
}

EBTNodeResult::Type UGetPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    FBTGetPatrolPointMemory* MyNodeMemory = GetSpecialNodeMemory<FBTGetPatrolPointMemory>(NodeMemory);

    AAIController* AIOwner = OwnerComp.GetAIOwner();

    if (IEnemyInterface* Enemy = Cast<IEnemyInterface>(AIOwner))
    {
        const TArray<AActor*>& PatrolPoints = Enemy->GetPatrolPts();

        if (PatrolPoints.Num() < 2)
        return EBTNodeResult::Failed;

        FVector TargetLocation = PatrolPoints[MyNodeMemory->PatrolIndex]->GetActorLocation();

        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TargetLocation);

        if (MyNodeMemory->PatrolIndex < Enemy->GetPatrolPts().Num() - 1)
        {
            MyNodeMemory->PatrolIndex++;
        }
        else
        {
            MyNodeMemory->PatrolIndex = 0;
        }

        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
