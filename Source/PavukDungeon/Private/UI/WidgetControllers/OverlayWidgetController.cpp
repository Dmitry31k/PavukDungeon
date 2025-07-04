// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/OverlayWidgetController.h"
#include "Components/GameplayComponents/HealthComponent.h"

void UOverlayWidgetController::BroadcastInitialValue()
{
    OnCurrentHealthUpdated.Broadcast(HealthComponent->GetCurrentHealth());
    OnMaxHealthUpdated.Broadcast(HealthComponent->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbaksToDelegates()
{
    HealthComponent->OnCurrentHealthChanged.AddDynamic(this, &UOverlayWidgetController::UpdateCurrentHealth);
    HealthComponent->OnMaxHealthChanged.AddDynamic(this, &UOverlayWidgetController::UpdateMaxHealth);
}

void UOverlayWidgetController::UpdateCurrentHealth(float NewCurrentHealth)
{
    OnCurrentHealthUpdated.Broadcast(NewCurrentHealth);
}

void UOverlayWidgetController::UpdateMaxHealth(float NewMaxHealth)
{
    OnMaxHealthUpdated.Broadcast(NewMaxHealth);
}