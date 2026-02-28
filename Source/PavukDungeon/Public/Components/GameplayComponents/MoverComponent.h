// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoverComponent.generated.h"

class IDeathInterface;
class IActivatableInterface;

template <typename RetVal, typename... ParamTypes>
using FunctPtr = TFunction<RetVal(ParamTypes...)>;

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

private:

  void MoveOwner(float DeltaTime);
  void SetOwnerLocationAndRotation(const FVector& DestinationLocation, const FRotator& DestinationRotation, const float& DeltaTime);

  // Offset that defines the direction and distance to move the actor
  UPROPERTY(EditAnywhere, category = "Movement")
  FVector MoveOffset { FVector::ZeroVector };

  // Offset that defines the direction and degree to rotate the actor
  UPROPERTY(EditAnywhere, category = "Movement")
  FRotator RotationOffset { FRotator::ZeroRotator };

  FVector StartLocation;
  FVector TargetLocation;

  FRotator StartRotation;
  FRotator TargetRotation;

  UPROPERTY(EditAnywhere, category = "Movement")
  float MovementSpeed { 100.f };

  UPROPERTY(EditAnywhere, category = "Movement")
  float RotationSpeed { 75.f };

  UPROPERTY(EditAnywhere, category = "Movement")
  bool bSmoothMovement { true };

  UPROPERTY(EditAnywhere, category = "Logs")
  bool bPrintTickLog { false };

  bool bMoveToDestination { false };

  // Movement is triggered when all actors with this tag are destroyed
  UPROPERTY(EditAnywhere, category = "Activation")
  FName ToKillActorTagName { NAME_None };
  // Movement is triggered when all actors with this tag are activated
  UPROPERTY(EditAnywhere, category = "Activation")
  FName ToActivateActorTagName { NAME_None };

  UPROPERTY()
  TArray<AActor*> FoundToKillActors;
  UPROPERTY()
  TArray<AActor*> FoundToActivateActors;

  UFUNCTION()
  void HandleDeathOrActivationActor(AActor* DeadOrActivatedActor);
  UFUNCTION()
  void HandleDeactivationActor(AActor* DeactivatedActor);

  // For each pair (Tag, Callback) in ArrayToCallbacks
  // finds all actors with the tag and calls the corresponding Callback on each actor
  void BindCallbacksToTaggedActors();

  // Binds specefic function to Tag Name
  TMap<FName, FunctPtr<void, AActor*>> ArrayToCallbacks;

  void InitArrayToCallbacks();
};
