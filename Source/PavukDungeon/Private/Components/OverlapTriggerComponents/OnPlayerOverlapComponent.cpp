// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/OverlapTriggerComponents/OnPlayerOverlapComponent.h"
#include "Kismet/GameplayStatics.h"

void UOnPlayerOverlapComponent::BeginPlay()
{
    Super::BeginPlay();

    PlayerActor = static_cast<AActor*>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void UOnPlayerOverlapComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor == PlayerActor)
    {
        PlayerStartOverlap(OverlappedComponent, OtherActor, OtherComp);
    }
}

void UOnPlayerOverlapComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor == PlayerActor)
    {
        PlayerEndOverlap(OverlappedComponent, OtherActor, OtherComp);
    }
}

void UOnPlayerOverlapComponent::PlayerStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
}
void UOnPlayerOverlapComponent::PlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
}
