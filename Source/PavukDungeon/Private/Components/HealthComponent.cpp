// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "Characters/Pavuks/PlayerPavuk.h"
#include "Characters/BaseCharacter.h"
#include "Actors/BaseActor.h"
#include "Interfaces/DeathInterface.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	OwnerActor = GetOwner();
	OwnerActor->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	if (DamagedActor == OwnerActor)
	{
		SetClampedCurrentHealth(GetCurrentHealth() - Damage);
	}
}

float UHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

float UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

void UHealthComponent::SetCurrentHealth(float NewCurrentHealth)
{
	CurrentHealth = NewCurrentHealth;
	OnCurrentHealthChanged.Broadcast(CurrentHealth);
}

void UHealthComponent::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
	OnMaxHealthChanged.Broadcast(MaxHealth);
}

void UHealthComponent::SetClampedCurrentHealth(float NewCurrentHealth)
{
	if (bKillable)
	{
		SetCurrentHealth(FMath::Clamp(NewCurrentHealth, 0, MaxHealth));
	}

	IDeathInterface* OwnerActorDeathInterface = Cast<IDeathInterface>(OwnerActor);
	if (GetCurrentHealth() <= 0 && OwnerActorDeathInterface)
	{
		OwnerActorDeathInterface->HandleDeath();
	}
}

void UHealthComponent::SetKillable(bool bNewKillable)
{
	bKillable = bNewKillable;
}

bool UHealthComponent::GetKillable() const
{
	return bKillable;
}