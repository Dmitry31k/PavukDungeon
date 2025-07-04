// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/OverlapTriggerComponents/TickOptimizerBox.h"
#include "Characters/Pavuks/PlayerPavuk.h"

UTickOptimizerBox::UTickOptimizerBox()
{
    ComponentTags.Add("IgnoreDamage");
}

void UTickOptimizerBox::PlayerStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
    Super::PlayerStartOverlap(OverlappedComponent, OtherActor, OtherComp);

    if (Cast<APlayerPavuk>(OtherActor))
    {
        GetOwner()->SetActorTickEnabled(true);
    }
}

void UTickOptimizerBox::PlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
    Super::PlayerEndOverlap(OverlappedComponent, OtherActor, OtherComp);

    if (Cast<APlayerPavuk>(OtherActor))
    {
        GetOwner()->SetActorTickEnabled(false);
    }
}