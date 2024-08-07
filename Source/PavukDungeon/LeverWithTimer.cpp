// Fill out your copyright notice in the Description page of Project Settings.

#include "LeverWithTimer.h"

void ALeverWithTimer::ActivateLever()
{
    Super::ActivateLever();

    if (DeactivateTimer > 0)
    {
        GetWorldTimerManager().SetTimer(Deactivator, this, &ALeverWithTimer::DeactivateLever, DeactivateTimer, false);
    }
}

void ALeverWithTimer::DeactivateLever()
{
    LeverMesh->SetRelativeRotation(StartLeverMeshRotation);
    WasActivated = false;
}