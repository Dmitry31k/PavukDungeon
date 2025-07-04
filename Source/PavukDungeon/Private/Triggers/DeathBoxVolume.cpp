// Fill out your copyright notice in the Description page of Project Settings.


#include "Triggers/DeathBoxVolume.h"
#include "Characters/Pavuks/PlayerPavuk.h"
#include "Kismet/GameplayStatics.h"

ADeathBoxVolume::ADeathBoxVolume()
{

}

void ADeathBoxVolume::BeginPlay()
{
    Super::BeginPlay();

    OnActorBeginOverlap.AddDynamic(this, &ADeathBoxVolume::OverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &ADeathBoxVolume::OnEndOverlap);

    PlayerPavuk = Cast<APlayerPavuk>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

    if (PlayerPavuk)
    {
        DamageTimerDelegate.BindUFunction(this, FName("DamageOverlappedActor"), PlayerPavuk);
    }
}

void ADeathBoxVolume::OverlapBegin(AActor* OverlappedActor, AActor* OverlappingActor)
{   
    if (PlayerPavuk && PlayerPavuk == OverlappingActor)
    {
        UGameplayStatics::ApplyDamage(OverlappingActor, DamageForPlayer, GetInstigatorController(), this, UDamageType::StaticClass());
        GetWorldTimerManager().SetTimer(DamageTimer, DamageTimerDelegate, ApplyDamageTimer, true);  
    } 
}

void ADeathBoxVolume::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    GetWorldTimerManager().ClearTimer(DamageTimer);
}

void ADeathBoxVolume::DamageOverlappedActor(AActor* DamagedActor)
{
    UGameplayStatics::ApplyDamage(DamagedActor, DamageForPlayer, GetInstigatorController(), this, UDamageType::StaticClass());
}