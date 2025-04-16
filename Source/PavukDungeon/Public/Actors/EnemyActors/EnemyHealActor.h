// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/EnemyActors/BaseEnemyActor.h"
#include "EnemyHealActor.generated.h"

class USphereComponent;

UENUM(BlueprintType)
enum class EHealPolicy : uint8
{
	HealOnly,
	MakeEnemiesImmortals
};

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API AEnemyHealActor : public ABaseEnemyActor
{
	GENERATED_BODY()

public:

	AEnemyHealActor();

protected:

	UPROPERTY(EditDefaultsOnly, category = "Visual")
	UStaticMeshComponent* HealCrystalBase;
	UPROPERTY(EditDefaultsOnly, category = "Visual")
	USkeletalMeshComponent* HealingHeart;

	virtual void BeginPlay() override;

	virtual void HandleDeath() override;

	UPROPERTY()
	TArray<AActor*> ActorsInRangeOfHeal;

private:

	UPROPERTY(EditDefaultsOnly, category = "Combat")
	USphereComponent* RangeOfHeal;

	UFUNCTION()
	void OnRangeOfWorkBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnRangeOfWorkEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(EditAnywhere, category = "Combat")
	EHealPolicy HealPolicy = EHealPolicy::MakeEnemiesImmortals;

	FTimerHandle HealTimerHandle;
	UPROPERTY(EditAnywhere, category = "Combat")
	float HealTimer = 0;
	UPROPERTY(EditAnywhere, category = "Combat")
	float ToHealHp = 5;

	void SetKillableForActor(AActor* Actor, bool bNewKillable);
	void HealAllActorsInRange();

	UPROPERTY()
	AActor* PlayerActor;
};
