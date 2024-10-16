// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EnemyActors/BaseEnemyActor.h"
#include "Components/HealthComponent.h"

ABaseEnemyActor::ABaseEnemyActor()
{
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Actor Health Component"));
}