// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChangeDroneColor.h"
#include "ShootingDrone.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SpotLightComponent.h"
#include "Math/Color.h"

UBTTask_ChangeDroneColor::UBTTask_ChangeDroneColor()
{
    NodeName = "Change drone backlight color";
}

EBTNodeResult::Type UBTTask_ChangeDroneColor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AShootingDrone* Drone = Cast<AShootingDrone>(OwnerComp.GetAIOwner()->GetPawn());

    if (Drone == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    Drone->VisionBacklight->SetLightColor(NewColor);
    return EBTNodeResult::Succeeded;
}