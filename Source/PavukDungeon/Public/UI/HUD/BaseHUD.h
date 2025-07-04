// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

class UBaseUserWidget;
class UOverlayWidgetController;
class UHealthComponent;

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<UBaseUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOrInitOverlayWidgetController(APlayerController* InPlayerController, UHealthComponent* InHealthComponent);
	void InitOverlay(APlayerController* InPlayerController, UHealthComponent* InHealthComponent);

private:

	UPROPERTY(EditAnywhere, category = "Overlay")
	TSubclassOf<UBaseUserWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere, category = "Overlay")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
};
