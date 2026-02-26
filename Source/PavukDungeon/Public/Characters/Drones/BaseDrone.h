// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interfaces/EnemyVisionInterface.h"
#include "BaseDrone.generated.h"

UCLASS()
class PAVUKDUNGEON_API ABaseDrone : public ABaseCharacter, public IEnemyVisionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseDrone();

	// IEnemyVisionInterface start
	virtual bool CanEnemySeePlayer() override { return bCanSeePlayer; }
	virtual FVector GetPlayerLocation() override;
	// IEnemyVisionInterface end

protected:
	
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* DroneFan;

	bool bCanSeePlayer { false };	


};
