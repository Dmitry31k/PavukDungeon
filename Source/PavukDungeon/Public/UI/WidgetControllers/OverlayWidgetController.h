// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetControllers/WidgetControllerBase.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentHealthUpdatedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthUpdatedSignature, float, NewMaxHealth);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PAVUKDUNGEON_API UOverlayWidgetController : public UWidgetControllerBase
{
	GENERATED_BODY()

public:

	virtual void BroadcastInitialValue() override;

	UPROPERTY(BlueprintAssignable, category = "Attributes")
	FOnCurrentHealthUpdatedSignature OnCurrentHealthUpdated;

	UPROPERTY(BlueprintAssignable, category = "Attributes")
	FOnMaxHealthUpdatedSignature OnMaxHealthUpdated;

	void BindCallbaksToDelegates();

protected:

	UFUNCTION()
	void UpdateCurrentHealth(float NewCurrentHeath);
	UFUNCTION()
	void UpdateMaxHealth(float NewMaxHealth);
	
};
