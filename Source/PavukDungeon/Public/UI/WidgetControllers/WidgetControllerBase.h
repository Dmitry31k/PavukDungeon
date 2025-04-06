// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetControllerBase.generated.h"

class UHealthComponent;
class PlayerController;

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UWidgetControllerBase : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	virtual void SetWidgetControllerParams(APlayerController* NewPlayerController, UHealthComponent* NewHealthComponent);

	virtual void BroadcastInitialValue();
	
protected:

	UPROPERTY(BlueprintReadOnly, category = "Widget controller")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, category = "Widget controller")
	TObjectPtr<UHealthComponent> HealthComponent;

};
