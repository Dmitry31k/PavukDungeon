// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PAVUKDUNGEON_API UMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

  UPROPERTY()
  TArray<AActor*> AliveActors;
  UPROPERTY()
  TArray<AActor*> NotActivatedUnlockerActors;

  void MoveToTargetLocation();
  void MoveToStartLocation();

private:

  UPROPERTY(EditAnywhere, category = "movement")
  FVector MoveOffset;
  FVector StartLocation;
  FVector TargetLocation;

  UPROPERTY(EditAnywhere, category = "movement")
  float MovementSpeed = 100;

};
