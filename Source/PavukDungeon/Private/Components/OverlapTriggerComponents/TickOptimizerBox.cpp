// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/OverlapTriggerComponents/TickOptimizerBox.h"
#include "Characters/Pavuks/PlayerPavuk.h"

UTickOptimizerBox::UTickOptimizerBox()
{
    ComponentTags.Add("IgnoreDamage");
}

void UTickOptimizerBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

    if (Cast<APlayerPavuk>(OtherActor))
    {
        GetOwner()->SetActorTickEnabled(true);
    }
}

void UTickOptimizerBox::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

    if (Cast<APlayerPavuk>(OtherActor))
    {
        GetOwner()->SetActorTickEnabled(false);
    }
}