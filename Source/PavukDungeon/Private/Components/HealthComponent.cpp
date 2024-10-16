// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "Characters/Pavuks/PlayerPavuk.h"
#include "Characters/BaseCharacter.h"
#include "Actors/BaseActor.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	OwnerActor = GetOwner();
	OwnerActor->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	OwnerCharacter = Cast<ABaseCharacter>(OwnerActor);
	OwnerBaseActor = Cast<ABaseActor>(OwnerActor);
}

void UHealthComponent::DamageTaken (AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	CurrentHealth -= Damage;
	if (CurrentHealth <= 0 && DamagedActor == OwnerActor && OwnerActor)
	{
		if (OwnerCharacter)
		{
			OwnerCharacter->CharacterDied();
		}
		else if (OwnerBaseActor)
		{
			OwnerBaseActor->ActorDied();
		}
	}
}