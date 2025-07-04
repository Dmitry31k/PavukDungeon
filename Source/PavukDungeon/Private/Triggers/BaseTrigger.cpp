// Fill out your copyright notice in the Description page of Project Settings.


#include "Triggers/BaseTrigger.h"
#include "Kismet/GameplayStatics.h"

ABaseTrigger::ABaseTrigger()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ABaseTrigger::BeginPlay()
{
    Super::BeginPlay();

    OnActorBeginOverlap.AddDynamic(this, &ABaseTrigger::OverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &ABaseTrigger::OverlapEnd);
}

void ABaseTrigger::OverlapBegin(AActor* OverlappedActor, AActor* OverlappingActor)
{

}
void ABaseTrigger::OverlapEnd(AActor* OverlappedActor, AActor* OverlappingActor)
{
    
}