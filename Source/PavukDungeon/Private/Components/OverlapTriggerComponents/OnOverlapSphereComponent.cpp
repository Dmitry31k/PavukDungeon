// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/OverlapTriggerComponents/OnOverlapSphereComponent.h"

void UOnOverlapSphereComponent::BeginPlay()
{
    Super::BeginPlay();

    OnComponentBeginOverlap.AddDynamic(this, &UOnOverlapSphereComponent::OnOverlapBegin);
    OnComponentEndOverlap.AddDynamic(this, &UOnOverlapSphereComponent::OnOverlapEnd);
}

void UOnOverlapSphereComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void UOnOverlapSphereComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}