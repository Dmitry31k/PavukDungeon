// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EnemyActors/OverlapBoxActors/EnemyActorWithOverlapBoxComp.h"
#include "Components/BoxComponent.h"

AEnemyActorWithOverlapBoxComp::AEnemyActorWithOverlapBoxComp()
{
    TriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TurretRotationTrigger"));
    TriggerBoxComponent->ComponentTags.Add(FName("IgnoreDamage"));
    RootComponent = TriggerBoxComponent;
}

void AEnemyActorWithOverlapBoxComp::BeginPlay()
{
    Super::BeginPlay();

    TriggerBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActorWithOverlapBoxComp::TriggerBoxComponentBeginOverlap);
    TriggerBoxComponent->OnComponentEndOverlap.AddDynamic(this, &AEnemyActorWithOverlapBoxComp::TriggerBoxComponentEndOverlap);
}

void AEnemyActorWithOverlapBoxComp::TriggerBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    
}

void AEnemyActorWithOverlapBoxComp::TriggerBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}