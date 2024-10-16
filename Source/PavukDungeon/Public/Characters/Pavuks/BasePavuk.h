// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "BasePavuk.generated.h"

UCLASS()
class PAVUKDUNGEON_API ABasePavuk : public ABaseCharacter
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
	virtual void MeleeAttack();

	UFUNCTION()
	virtual void OverlapJawDamagerBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void OverlapJawDamagerEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	virtual void OverlapTailDamagerBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditDefaultsOnly, category = "movement")
	float GrabDistance = 150;
	UPROPERTY(EditDefaultsOnly, category = "movement")
	float HoldDistance = 125;

	UPROPERTY(EditdefaultsOnly, category = "combat")
	float MeleeDamage = 30;

	FHitResult GrabHitResult;
	float GrabSphereRadius = 30;

	UPROPERTY()
	class UPhysicsHandleComponent* PhysicsHandle;

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
	bool WasMeleeDamage = false;

	FTimerHandle SetShootTimerHandle;
	FTimerHandle SetWasMeleeDamagedTimerHandle;

	UPROPERTY(EditdefaultsOnly, category = "combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditdefaultsOnly, category = "combat")
	float RechargingShootSpeed = 3;

	UPROPERTY(EditdefaultsOnly, category = "combat")
	float RechargingMeleeDamageSpeed = 0.25;
	
	virtual void SetCanShootTrue();
	virtual void SetWasMeleeDamageFalse();

	UPROPERTY(EditAnywhere)
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* BoxDamagerTail;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* BoxDamagerJaw;

	UPROPERTY(EditDefaultsOnly, category = "Animation")
	UAnimMontage* TailAttack;

	UPROPERTY(EditDefaultsOnly, category = "Animation")
	UAnimMontage* JawAttack;

	TArray<UAnimMontage*> MeleeAttacksArray;

	UPROPERTY()
	AActor* HaveToDamageActor;
};
