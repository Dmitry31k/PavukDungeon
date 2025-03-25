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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void CharacterDied() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Grab() override;
	void Release() override;
	void Shoot() override;
	void MeleeAttack() override;

private:

	void MoveForward(float Scale);
	void TurnRight(float Scale);
	void Interact();

	UPROPERTY(VisibledefaultsOnly)
	class UCameraComponent* Camera;
	UPROPERTY(VisibledefaultsOnly)
	class USpringArmComponent* Arm;

	UPROPERTY()
	class ADefaultPlayerController* DefaultPlayerController;

	UPROPERTY(EditDefaultsOnly)
	float InteractDistance = 200;

	UPROPERTY()
	class ALever* Lever;

	void ActivateLever(FHitResult ActivateLeverHitResult);

	UPROPERTY(EditdefaultsOnly, category = "combat")
	float RechargingShootSpeed = 2;
	bool CanShoot = true;
	FTimerHandle SetShootTimerHandle;

	void SetCanShootTrue();
	void SetWasMeleeDamageFalse();

	UPROPERTY(EditdefaultsOnly, category = "combat")
	float RechargingMeleeDamageSpeed = 0.25;
	bool WasMeleeDamage = false;
	FTimerHandle SetWasMeleeDamagedTimerHandle;
};