// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasePavuk.generated.h"

UCLASS()
class PAVUKDUNGEON_API ABasePavuk : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasePavuk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Grab();
	virtual void Release();

	UPROPERTY(EditDefaultsOnly, category = "movement")
	float GrabDistance = 150;
	UPROPERTY(EditDefaultsOnly, category = "movement")
	float HoldDistance = 125;

	FHitResult GrabHitResult;
	float GrabSphereRadius = 30;

	bool WasHit;

	class UPhysicsHandleComponent* PhysicsHandle;

	virtual void PavukDied();
	virtual void Shoot();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleDefaultsOnly)
	class USphereComponent* SphereCollision1;
	UPROPERTY(VisibleDefaultsOnly)
	class USphereComponent* SphereCollision2;
	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent* ProjectileSpawnPoint;

	bool CanShoot = true;
	FTimerHandle SetShootTimerHandle;

	UPROPERTY(EditdefaultsOnly, category = "combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditdefaultsOnly, category = "combat")
	float RechargingShootSpeed = 3;
	
	virtual void SetCanShootTrue();
};
