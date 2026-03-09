// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/ChangeLightColor.h"
#include "Interfaces/LightInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SpotLightComponent.h"
#include "Math/Color.h"

UChangeLightColor::UChangeLightColor()
{
    NodeName = "Change drone backlight color";
}

EBTNodeResult::Type UChangeLightColor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ILightInterface* LightInterface = Cast<ILightInterface>(OwnerComp.GetAIOwner()->GetPawn());

    if (LightInterface == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    for (USpotLightComponent* Light : LightInterface->GetAllLightComps())
    {
        Light->SetLightColor(NewColor);
    }

    return EBTNodeResult::Succeeded;
}