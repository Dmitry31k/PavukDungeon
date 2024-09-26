// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGamemode.h"
#include "DefaultPlayerController.h"
#include "Kismet/GameplayStatics.h"

void ADefaultGamemode::PlayerDied(ADefaultPlayerController* DiedPlayersController)
{
    if (DiedPlayersController)
    {
        DiedPlayersController->GameHasFinished(false);
    }
}