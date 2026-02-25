// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoverComponent.generated.h"

class IDeathInterface;
class IActivatableInterface;


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

  virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:

private:

  UPROPERTY(EditAnywhere, category = "Movement")
  FVector MoveOffset;
  FVector StartLocation;
  FVector TargetLocation;

  UPROPERTY(EditAnywhere, category = "Movement")
  float MovementSpeed = 100;

  UPROPERTY(EditAnywhere, category = "Movement")
  bool bSmoothMovement = true;

  UPROPERTY(EditAnywhere, category = "Logs")
  bool bPrintTickLog = false;

  bool bMoveToTargetLocation = false;

  UPROPERTY(EditAnywhere, category = "Activation")
  FName ToKillActorTagName { NAME_None };
  UPROPERTY(EditAnywhere, category = "Activation")
  FName ToActivateActorTagName { NAME_None };

  TArray<IActivatableInterface*> FoundToActivateInterfaces;
  TArray<IDeathInterface*> FoundToKillInterfaces;

  UFUNCTION()
  void HandleDeathOrActivationActor(AActor* DeadOrActivatedActor);
  UFUNCTION()
  void HandleDeactivationActor(AActor* DeactivatedActor);

};
