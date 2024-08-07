// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PAVUKDUNGEON_API UMover : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

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

	UPROPERTY(EditAnywhere, category = "movement")
	FVector MoveOffset;
	FVector StartLocation;

	UPROPERTY(EditAnywhere, category = "movement")
	float MovementSpeed = 100;

	UPROPERTY(EditAnywhere, category = "movement")
	FName UnlockerTag;

	class ALever* Lever;
	class APressurePlate* PressurePlate;
	TArray<AActor*> FoundActors;
};
