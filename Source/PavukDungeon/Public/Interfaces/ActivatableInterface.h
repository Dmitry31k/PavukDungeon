// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActivatableInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActivatedSignature, AActor*, ActivatedActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeactivatedSignature, AActor*, ActivatedActor);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActivatableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PAVUKDUNGEON_API IActivatableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual FOnActivatedSignature& GetOnActivatedDelegate() = 0;
	virtual FOnDeactivatedSignature& GetOnDeactivatedDelegate() = 0;
};
