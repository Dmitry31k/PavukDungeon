// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "MoverComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PAVUKDUNGEON_API UMoverComponent : public UBoxComponent
{
	GENERATED_BODY()

	public:	
	// Sets default values for this component's properties
	UMoverComponent();

	UPROPERTY(EditAnywhere, category = "movement")
	bool ShouldMove = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UFUNCTION()
	void MoveToTarget();

	bool CheckActor();
	bool WasKilledAllWithTag();

	UPROPERTY(EditAnywhere, category = "movement")
	FVector MoveOffset;
	FVector StartLocation;
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, category = "movement")
	float MovementSpeed = 100;

	UPROPERTY(EditAnywhere, category = "movement")
	FName UnlockerTag;

	UPROPERTY(EditAnywhere, category = "movement")
	FName ToKillTag;

	UPROPERTY()
	class ALever* Lever;

	UPROPERTY()
	class APressurePlate* PressurePlate;

	UPROPERTY()
	TArray<AActor*> FoundUnlockerActors;

	UPROPERTY()
	TArray<AActor*> FoundAliveActors;	
};
