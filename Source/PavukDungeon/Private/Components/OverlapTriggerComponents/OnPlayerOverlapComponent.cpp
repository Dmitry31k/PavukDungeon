// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/OverlapTriggerComponents/OnPlayerOverlapComponent.h"
#include "Characters/Pavuks/PlayerPavuk.h"

void UOnPlayerOverlapComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor == GetOwner())
    return;

    if (OtherActor->IsA(APlayerPavuk::StaticClass()) && !OverlappedPlayer)
    {
        PlayerStartOverlap(OverlappedComponent, OtherActor, OtherComp);
        OnStartOverlappedByPlayer.Broadcast(GetOwner(), this, OtherActor);
        OverlappedPlayer = OtherActor;
    }
}

void UOnPlayerOverlapComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor == GetOwner())
    return;

    if (!OverlappedComponent->IsOverlappingActor(OverlappedPlayer) && OverlappedPlayer)
    {
        PlayerEndOverlap(OverlappedComponent, OtherActor, OtherComp);
        OnEndOverlappedByPlayer.Broadcast(GetOwner(), this, OtherActor);
        OverlappedPlayer = nullptr;
    }
}

void UOnPlayerOverlapComponent::PlayerStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
}
void UOnPlayerOverlapComponent::PlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
}
