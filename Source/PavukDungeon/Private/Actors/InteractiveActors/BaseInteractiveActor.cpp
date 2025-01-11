// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractiveActors/BaseInteractiveActor.h"
#include "Components/MoverComponent.h"
#include "Kismet/GameplayStatics.h"

void ABaseInteractiveActor::BeginPlay()
{
    Super::BeginPlay();

    if (!MoverComponentTag.IsNone())
    {
        UGameplayStatics::GetAllActorsWithTag(GetWorld(), MoverComponentTag, FoundActorWithTag);

        if (FoundActorWithTag.Num() > 0)
        {
            UnlockerComponent = Cast<UMoverComponent>(FoundActorWithTag[0]->FindComponentByClass<UMoverComponent>());
        }

        AddActorIntoNotActivatedUnlockerActors();
    }
}

void ABaseInteractiveActor::AddActorIntoNotActivatedUnlockerActors()
{
    if (!UnlockerComponent)
    {
        return;
    }
    UnlockerComponent->NotActivatedUnlockerActors.Add(this);
    UnlockerComponent->MoveToStartLocation();
}

void ABaseInteractiveActor::DeleteActorFromNotActivatedUnlockerActors()
{
    if (!UnlockerComponent)
    {
        return;
    }
    UnlockerComponent->NotActivatedUnlockerActors.Remove(this);
    UnlockerComponent->MoveToTargetLocation();
}