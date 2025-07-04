// Fill out your copyright notice in the Description page of Project Settings.


#include "Triggers/DeathBoxVolume.h"
#include "Characters/Pavuks/PlayerPavuk.h"
#include "Kismet/GameplayStatics.h"

void ADeathBoxVolume::PlayerStartOverlap(AActor* OverlappedActor, AActor* OverlappingActor)
{   
    DamagePlayer();
    GetWorldTimerManager().SetTimer(DamageTimer, this, &ADeathBoxVolume::DamagePlayer, ApplyDamageTimer, true);
}

void ADeathBoxVolume::PlayerEndOverlap(AActor* OverlappedActor, AActor* OverlappingActor)
{
    GetWorldTimerManager().ClearTimer(DamageTimer);
}

void ADeathBoxVolume::DamagePlayer()
{
    UGameplayStatics::ApplyDamage(PlayerActor.Get(), DamageForPlayer, GetInstigatorController(), this, UDamageType::StaticClass());
}