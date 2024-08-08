// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePavuk.h"
#include "PlayerPavuk.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API APlayerPavuk : public ABasePavuk
{
	GENERATED_BODY()
	
public:

	APlayerPavuk();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PavukDied();
	bool IsAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Grab();
	void Release();
	void Shoot();

private:

	void MoveForward(float Scale);
	void TurnRight(float Scale);
	void Interact();

	UPROPERTY(VisibledefaultsOnly)
	class UCameraComponent* Camera;

	UPROPERTY(VisibledefaultsOnly)
	class USpringArmComponent* Arm;

	APlayerController* Controller;

	UPROPERTY(EditDefaultsOnly)
	float InteractDistance = 200;

	class ALever* Lever;

	void ActivateLever(FHitResult ActivateLeverHitResult);
};