// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EnemyActors/BaseEnemyActor.h"
#include "Components/HealthComponent.h"
#include "Components/MoverComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseEnemyActor::ABaseEnemyActor()
{
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Actor Health Component"));
}

void ABaseEnemyActor::BeginPlay()
{
    Super::BeginPlay();

    if (!MoverComponentTag.IsNone())
    {
        UGameplayStatics::GetAllActorsWithTag(GetWorld(), MoverComponentTag, FoundActorWithTag);

        if (FoundActorWithTag.Num() > 0)
        {
            UnlockerComponent = Cast<UMoverComponent>(FoundActorWithTag[0]->FindComponentByClass<UMoverComponent>());
        }

        AddActorIntoAliveActors();
    }
}

void ABaseEnemyActor::HandleDeath()
{
    Super::HandleDeath();
    
    DeleteActorFromAliveActors();
}

void ABaseEnemyActor::AddActorIntoAliveActors()
{
    if (!UnlockerComponent)
    {
        return;
    }
    UnlockerComponent->AliveActors.Add(this);
    UnlockerComponent->MoveToStartLocation();
}

void ABaseEnemyActor::DeleteActorFromAliveActors()
{
    if (!UnlockerComponent)
    {
        return;
    }
    UnlockerComponent->AliveActors.Remove(this);
    UnlockerComponent->MoveToTargetLocation();
}

UHealthComponent* ABaseEnemyActor::GetHealthComponent()
{
    return HealthComponent;
}