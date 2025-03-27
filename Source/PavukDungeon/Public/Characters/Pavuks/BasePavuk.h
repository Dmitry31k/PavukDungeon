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

	virtual void Shoot() override;
	virtual void MeleeAttack() override;

public:

private:

	UPROPERTY(VisibleDefaultsOnly)
	class UBoxComponent* CharacterBoxCollision;

	bool IsHoldingObject = false;

	void UpdatePhysicsHandleComponent();

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

	UPROPERTY()
	UAnimMontage* CurrentAnimMontage;

	TArray<UAnimMontage*> MeleeAttacksArray;

	UPROPERTY()
	AActor* HaveToDamageActor;
	UPROPERTY()
	AActor* DamagedActor;

	void ClearDamagedActor(UAnimMontage* Montage, bool bInterrupted);

	void DamageActor(AActor* ToDamageActor);
};