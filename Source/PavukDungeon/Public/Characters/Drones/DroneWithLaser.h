// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Drones/BaseDrone.h"
#include "DroneWithLaser.generated.h"

class UNiagaraComponent;
class UTickOptimizerBox;
enum class EMovingType : uint8;

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

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, category = "Combat")
	float LaserLength = 500;

	UPROPERTY(EditDefaultsOnly, category = "Combat")
	float LaserDamage = 100;

	bool IsBlockingLaser = false;

	FHitResult LineTraceHitResult;

	UPROPERTY()
	class APlayerPavuk* PlayerPavuk;

	void LaserShoot();
	void CheckIfPlayerTouchedLaser();

	//Vector that will be send into AI controller for using in behavior tree
	UPROPERTY(EditAnywhere, category = "Combat")
	FVector FirstMoveOffset_Drone;
	//Vector that will be send into AI controller for using in behavior tree
	UPROPERTY(EditAnywhere, category = "Combat")
	FVector SecondMoveOffset_Drone;
	//Vector that will be send into AI controller for using in behavior tree
	UPROPERTY(EditAnywhere, category = "Combat")
	FVector ThirdMoveOffset_Drone;
	//Vector that will be send into AI controller for using in behavior tree
	UPROPERTY(EditAnywhere, category = "Combat")
	FVector FourthMoveOffset_Drone;
	//Vector that will be send into AI controller for using in behavior tree
	UPROPERTY(EditAnywhere, category = "Combat")
	FVector FifthMoveOffset_Drone;
	//Enum that determine type of behavior
	UPROPERTY(EditAnywhere, category = "Combat")
	EMovingType MovingPolicy;

	UPROPERTY(EditDefaultsOnly, category = "Combat")
	UTickOptimizerBox* ActiveTickZone;

	//Function that send Vectors & bools variables into AI controller for using into behavior script
	void SendDataIntoAIController(class AAIController_DroneWithLaser* OwnerAIController);

	UPROPERTY(EditDefaultsOnly, category = "Visual")
	UNiagaraComponent* LaserNiagaraComponent;

	UPROPERTY(EditDefaultsOnly, category = "Visual")
	UNiagaraSystem* LaserFlashNiagaraSystem;

};
