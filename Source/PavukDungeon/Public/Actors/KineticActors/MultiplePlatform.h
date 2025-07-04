// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseKineticActor.h"
#include "MultiplePlatform.generated.h"

UCLASS()
class PAVUKDUNGEON_API AMultiplePlatform : public ABaseKineticActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMultiplePlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditAnywhere, category = "movement")
	FVector MovingSpeed = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, category = "movement")
	FVector MovingDistance = FVector::ZeroVector;
	
	//Showing to us where was point from platform start moving
	FVector StartLocation;

	//Showing to us distance that platform managed to move
	float DistanceMoved = 0;

	//Function for moving platform with speed(MovingSpeed) to a distance(MovingDistance)
	void SetPlatformNewLocation(float DeltaTime);

	UPROPERTY(EditAnywhere, category = "movement")
	float TimerDissapear = 0;
	UPROPERTY(EditAnywhere, category = "movement")
	float TimerApear = 0;
	
	FTimerHandle MainCount;
	FTimerHandle DisableTimer;
	FTimerHandle EnableTimer;

	void PlatformDisable();
	void PlatformEnable();	

};
