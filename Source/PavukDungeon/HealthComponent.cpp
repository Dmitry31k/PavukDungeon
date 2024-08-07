// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "PlayerPavuk.h"

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

	PlayerPavuk = Cast<APlayerPavuk>(OwnerActor);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken (AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	CurrentHealth -= Damage;
	if (CurrentHealth <= 0 && DamagedActor == OwnerActor)
	{
		if (PlayerPavuk)
		{
			PlayerPavuk->PavukDied();
		}
		else if (OwnerActor)
		{
			OwnerActor->Destroy();
		}
	}
}