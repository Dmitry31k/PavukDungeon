// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/OverlapTriggerComponents/TickOptimizer.h"
#include "Characters/Pavuks/PlayerPavuk.h"

UTickOptimizer::UTickOptimizer()
{
    ComponentTags.Add("IgnoreDamage");
}

void UTickOptimizer::PlayerStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
    Super::PlayerStartOverlap(OverlappedComponent, OtherActor, OtherComp);

    GetOwner()->SetActorTickEnabled(true);
}

void UTickOptimizer::PlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
    Super::PlayerEndOverlap(OverlappedComponent, OtherActor, OtherComp);

    GetOwner()->SetActorTickEnabled(false);
}