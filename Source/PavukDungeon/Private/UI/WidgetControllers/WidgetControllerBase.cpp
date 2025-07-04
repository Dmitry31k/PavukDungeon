// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/WidgetControllerBase.h"

void UWidgetControllerBase::SetWidgetControllerParams(APlayerController* NewPlayerController, UHealthComponent* NewHealthComponent)
{
    PlayerController = NewPlayerController;
    HealthComponent = NewHealthComponent;
}

void UWidgetControllerBase::BroadcastInitialValue()
{

}