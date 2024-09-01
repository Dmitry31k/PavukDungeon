// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDrone.h"
#include "DroneWithLaser.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API ADroneWithLaser : public ABaseDrone
{
	GENERATED_BODY()
	
public:
	
	ADroneWithLaser();

	virtual void Tick(float DeltaTime) override;

	//Vector that will be send into AI controller for using in node "MoveTo"
	UPROPERTY(EditAnywhere)
	FVector FirstMoveOffset = FVector::ZeroVector;
	//Vector that will be send into AI controller for using in node "MoveTo"
	UPROPERTY(EditAnywhere)
	FVector SecondMoveOffset = FVector::ZeroVector;
	//Vector that will be send into AI controller for using in node "MoveTo"
	UPROPERTY(EditAnywhere)
	FVector ThirdtMoveOffset = FVector::ZeroVector;
	//Vector that will be send into AI controller for using in node "MoveTo"
	UPROPERTY(EditAnywhere)
	FVector FourthMoveOffset = FVector::ZeroVector;
	//Vector that will be send into AI controller for using in node "MoveTo"
	UPROPERTY(EditAnywhere)
	FVector FifthMoveOffset = FVector::ZeroVector;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	float LaserLength = 500;

	UPROPERTY(EditDefaultsOnly)
	float LaserDamage = 100;

	bool IsBlockingLaser = false;

	FHitResult LineTraceHitResult;

	UPROPERTY()
	class APlayerPavuk* PlayerPavuk;

	void LaserShoot();
	void CheckIfPlayerTouchedLaser();
};
