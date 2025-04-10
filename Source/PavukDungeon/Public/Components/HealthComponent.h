// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PAVUKDUNGEON_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	bool IsAlive = true;
	virtual float GetCurrentHealth() const;
	virtual float GetMaxHealth() const;
	virtual void SetCurrentHealth(float NewCurrentHealth);
	virtual void SetMaxHealth(float NewMaxHealth);

	UPROPERTY(BlueprintAssignable, category = "Variables")
	FOnCurrentHealthChangedSignature OnCurrentHealthChanged;

	UPROPERTY(BlueprintAssignable, category = "Variables")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

private:

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100;

	float CurrentHealth;

	UPROPERTY()
	AActor* OwnerActor;

	UFUNCTION()
	void DamageTaken (AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);
};
