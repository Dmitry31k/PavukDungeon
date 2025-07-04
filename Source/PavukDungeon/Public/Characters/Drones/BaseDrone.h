// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "BaseDrone.generated.h"

UCLASS()
class PAVUKDUNGEON_API ABaseDrone : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseDrone();

protected:
	
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* DroneFan;

public:	


};
