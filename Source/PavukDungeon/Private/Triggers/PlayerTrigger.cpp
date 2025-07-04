// Fill out your copyright notice in the Description page of Project Settings.


#include "Triggers/PlayerTrigger.h"
#include "Kismet/GameplayStatics.h"

void APlayerTrigger::BeginPlay()
{
    Super::BeginPlay();

    PlayerActor = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void APlayerTrigger::OverlapBegin(AActor* OverlappedActor, AActor* OverlappingActor)
{
    if (OverlappingActor == PlayerActor)
    {
        PlayerStartOverlap(OverlappedActor, OverlappingActor);
    }
}

void APlayerTrigger::OverlapEnd(AActor* OverlappedActor, AActor* OverlappingActor)
{
    if (OverlappingActor == PlayerActor)
    {
        PlayerEndOverlap(OverlappedActor, OverlappingActor);
    }
}

void APlayerTrigger::PlayerStartOverlap(AActor *OverlappedActor, AActor *OverlappingActor)
{
}
void APlayerTrigger::PlayerEndOverlap(AActor *OverlappedActor, AActor *OverlappingActor)
{
}
