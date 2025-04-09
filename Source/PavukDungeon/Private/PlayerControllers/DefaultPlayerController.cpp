// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/DefaultPlayerController.h"
#include "UI/HUD/BaseHUD.h"
#include "UI/Widgets/BaseUserWidget.h"

void ADefaultPlayerController::GameHasFinished(bool IsPlayerWon)
{
    if (ABaseHUD* ActiveHUD = Cast<ABaseHUD>(GetHUD()))
    {
        ActiveHUD->OverlayWidget->RemoveFromViewport();
    }
    

    if (IsPlayerWon)
    {

    }
    else
    {
        GameHasEnded();
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);

        if (LoseScreen)
        {   
            LoseScreen->AddToViewport();
        }
    }
}