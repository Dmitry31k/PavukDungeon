// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/DefaultPlayerController.h"
#include "Blueprint/UserWidget.h"

void ADefaultPlayerController::GameHasFinished(bool IsPlayerWon)
{
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