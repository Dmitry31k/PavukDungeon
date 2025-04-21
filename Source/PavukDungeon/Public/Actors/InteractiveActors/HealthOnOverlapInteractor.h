// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractiveActors/BaseInteractiveActor.h"
#include "HealthOnOverlapInteractor.generated.h"

class USphereComponent;
class UHealthComponent;

UENUM(BlueprintType)
enum class EHealthInteractionType : uint8
{
	Heal,
	Damage
};

UENUM(BlueprintType)
enum class EInteractionPolicy : uint8
{
	InteractOnStartOverlap,
	InteractOnEndOverlap,
	InteractDuringOverlapWithTimer,
	InteractAfterOverlapWithTimer
};

UENUM(BlueprintType)
enum class EDestroyPolicy : uint8
{
	DestroyOnBeginOverlap,
	DestroyOnEndOverlap,
	DoNotDestroy
};

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API AHealthOnOverlapInteractor : public ABaseInteractiveActor
{
	GENERATED_BODY()

public:

	AHealthOnOverlapInteractor();

	virtual void HandleDeath() override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, category = "Visual")
	UStaticMeshComponent* MeshForActor;
	UPROPERTY(EditDefaultsOnly, category = "Visual")
	USphereComponent* InteractSphere;

	UFUNCTION(BlueprintCallable)
	virtual void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	virtual void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, category = "Health Interaction")
	EHealthInteractionType HealthInteract;
	UPROPERTY(EditAnywhere, category = "Health Interaction")
	EInteractionPolicy InteractPolicy;
	UPROPERTY(EditAnywhere, category = "Health Interaction")
	EDestroyPolicy DestroyPolicy;
	UPROPERTY(EditAnywhere, category = "Health Interaction")
	float HealthChangeAmount;
	UPROPERTY(EditAnywhere, category = "Health Interaction")
	float ChangeHealthTimer;
	UPROPERTY(EditAnywhere, category = "Health Interaction")
	float HealthChangeClearDelay;

	UPROPERTY()
	AActor* PlayerActor;
	UPROPERTY()
	UHealthComponent* PlayerHealthComponent;

	FTimerHandle HealthChangeTimerHandle;
	FTimerHandle HealthChangeClearDelayTimerHandle;

	//Function for changing health for player based on EHealthInteractionType
	virtual void HandlePlayerHealthChange();

private:

	void DestroyAfterDelay();
	void ClearHealthChangeTimer();
	
};
