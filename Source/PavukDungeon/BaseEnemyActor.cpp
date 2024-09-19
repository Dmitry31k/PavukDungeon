// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyActor.h"
#include "HealthComponent.h"

ABaseEnemyActor::ABaseEnemyActor()
{
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Actor Health Component"));
}