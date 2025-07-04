// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/BaseHUD.h"
#include "UI/WidgetControllers/OverlayWidgetController.h"
#include "UI/Widgets/BaseUserWidget.h"

UOverlayWidgetController* ABaseHUD::GetOrInitOverlayWidgetController(APlayerController* InPlayerController, UHealthComponent* InHealthComponent)
{
    if (OverlayWidgetController == nullptr)
    {
        OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
        OverlayWidgetController->SetWidgetControllerParams(InPlayerController, InHealthComponent);
        OverlayWidgetController->BindCallbaksToDelegates();
    }

    return OverlayWidgetController;
}

void ABaseHUD::InitOverlay(APlayerController* InPlayerController, UHealthComponent* InHealthComponent)
{
    if (OverlayWidgetControllerClass == nullptr || OverlayWidgetClass == nullptr)
    {
        return;
    }

    UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
    OverlayWidget = Cast<UBaseUserWidget>(UserWidget);

    OverlayWidgetController = GetOrInitOverlayWidgetController(InPlayerController, InHealthComponent);
    OverlayWidget->SetWidgetController(OverlayWidgetController);

    OverlayWidgetController->BroadcastInitialValue();
    OverlayWidget->AddToViewport();
}