// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EnemyActors/EnemyHealActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Interfaces/DeathInterface.h"
#include "Components/GameplayComponents/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

AEnemyHealActor::AEnemyHealActor()
{
    HealCrystalBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base mesh for heal crystal"));
    RootComponent = HealCrystalBase;

    HealingHeart = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh for crystal itself"));
    HealingHeart->SetupAttachment(RootComponent);

    RangeOfHeal = CreateDefaultSubobject<USphereComponent>(TEXT("Mesh for determin radius of healing for this actor"));
    RangeOfHeal->SetupAttachment(RootComponent);
}

void AEnemyHealActor::BeginPlay()
{
    Super::BeginPlay();

    RangeOfHeal->OnComponentBeginOverlap.AddDynamic(this, &AEnemyHealActor::OnRangeOfWorkBeginOverlap);
    RangeOfHeal->OnComponentEndOverlap.AddDynamic(this, &AEnemyHealActor::OnRangeOfWorkEndOverlap);
    RangeOfHeal->GetOverlappingActors(ActorsInRangeOfHeal);

    PlayerActor = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    ActorsInRangeOfHeal.Remove(PlayerActor);

    switch (HealPolicy)
    {
        case EHealPolicy::HealOnly:

            GetWorldTimerManager().SetTimer(HealTimerHandle, this, &AEnemyHealActor::HealAllActorsInRange, HealTimer, true);
        break;

        case EHealPolicy::MakeEnemiesImmortals:

            for (auto Actor : ActorsInRangeOfHeal)
            {
                SetKillableForActor(Actor, false);
            }
        break;
    }
}

void AEnemyHealActor::OnRangeOfWorkBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OverlappedComponent->ComponentHasTag("IgnoreDamage") && OtherActor != PlayerActor)
    {
        ActorsInRangeOfHeal.AddUnique(OtherActor);
        SetKillableForActor(OtherActor, false);
    }
}

void AEnemyHealActor::OnRangeOfWorkEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!OverlappedComponent->ComponentHasTag("IgnoreDamage"))
    {
        ActorsInRangeOfHeal.Remove(OtherActor);
        SetKillableForActor(OtherActor, true);
    }
}

void AEnemyHealActor::HealAllActorsInRange()
{
    for (auto Actor : ActorsInRangeOfHeal)
    {
        if (IDeathInterface* ActorDeathInterface = Cast<IDeathInterface>(Actor))
        {
            if (UHealthComponent* ActorHealthComponent = ActorDeathInterface->GetHealthComponent())
            {
                ActorHealthComponent->SetClampedCurrentHealth(ActorHealthComponent->GetCurrentHealth() + ToHealHp);
            }
        }
    }
}

void AEnemyHealActor::SetKillableForActor(AActor* Actor, bool bNewKillable)
{
    if (IDeathInterface* ActorDeathInterface = Cast<IDeathInterface>(Actor))
    {
        if (UHealthComponent* ActorHealthComponent = ActorDeathInterface->GetHealthComponent())
        {
            ActorHealthComponent->SetKillable(bNewKillable);
        }
    }
}

void AEnemyHealActor::HandleDeath()
{
    if (HealPolicy == EHealPolicy::HealOnly)
    {
        GetWorldTimerManager().ClearTimer(HealTimerHandle);
    }
    else
    {
        for (auto Actor : ActorsInRangeOfHeal)
        {
            SetKillableForActor(Actor, true);
        }
    }

    // Execution logic before Super::HandleDeath() since Super destroys the component
    Super::HandleDeath();
}