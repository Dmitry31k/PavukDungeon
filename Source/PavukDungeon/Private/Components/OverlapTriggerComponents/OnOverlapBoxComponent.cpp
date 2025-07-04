// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/OverlapTriggerComponents/OnOverlapBoxComponent.h"

void UOnOverlapBoxComponent::BeginPlay()
{
    Super::BeginPlay();

    OnComponentBeginOverlap.AddDynamic(this, &UOnOverlapBoxComponent::OnOverlapBegin);
    OnComponentEndOverlap.AddDynamic(this, &UOnOverlapBoxComponent::OnOverlapEnd);
}

void UOnOverlapBoxComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void UOnOverlapBoxComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}