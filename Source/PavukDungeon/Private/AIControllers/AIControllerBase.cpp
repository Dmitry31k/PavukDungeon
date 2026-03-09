// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllers/AIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Characters/Pavuks/PlayerPavuk.h"
#include "Kismet/GameplayStatics.h"
#include "Components/GameplayComponents/PatrollingComponent.h"

void AAIControllerBase::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    checkf(BehaviorTreeClass, TEXT("Please set BehaviorTreeClass inside %s"), *GetNameSafe(this));
    RunBehaviorTree(BehaviorTreeClass);

    GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), InPawn->GetActorLocation());
    GetBlackboardComponent()->SetValueAsVector(TEXT("StartForwardVector"), InPawn->GetActorForwardVector() * 1000 + InPawn->GetActorLocation());

    InPawn->OnTakeAnyDamage.AddDynamic(this, &AAIControllerBase::HandleDamage);

    if (UPatrollingComponent* PatrollingComponent = InPawn->FindComponentByClass<UPatrollingComponent>())
    {
        PatrollingPoints = PatrollingComponent->GetPatrolPts();
        PatrollingType = PatrollingComponent->GetPatrolType();
        GetBlackboardComponent()->SetValueAsEnum(TEXT("PatrollingType"), static_cast<uint8>(PatrollingType));
    }
}

void AAIControllerBase::HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (AActor* DamageOwner = DamageCauser->GetOwner())
    {
        if (DamageOwner->IsA(APlayerPavuk::StaticClass()))
        {
            OnHitByPlayer.Broadcast(DamageOwner, this);
            bWasHitByPlayer = true;
        }
    }
}

FVector AAIControllerBase::GetPlayerLocation()
{
    FVector PlayerLocation = FVector::ZeroVector;

    if (APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0))
    {
        PlayerLocation = PlayerPawn->GetActorLocation();
    }

    return PlayerLocation;
}