// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlapEventPlatform.h"
#include "Components/BoxComponent.h"
#include "Timermanager.h"

AOverlapEventPlatform::AOverlapEventPlatform()
{
    HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerForPlatformDestructing"));
    HitBox->SetupAttachment(RootComponent);
}

void AOverlapEventPlatform::BeginPlay()
{
    Super::BeginPlay();
    OnActorBeginOverlap.AddDynamic(this, &AOverlapEventPlatform::OverlapBegin);
}

void AOverlapEventPlatform::OverlapBegin(AActor* OverlappedActor, AActor* OverlappingActor)
{
    if (OverlappedActor && OverlappingActor != this)
    {
        GetWorldTimerManager().SetTimer(DestructingPlatform, this, &AOverlapEventPlatform::DestructPlatform, DestructionTimer, false);
    }
}

void AOverlapEventPlatform::DestructPlatform()
{
    this->Destroy();
}