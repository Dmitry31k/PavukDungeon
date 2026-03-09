// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Actors/EnemyActors/Projectile.h"
#include "Components/GameplayComponents/HealthComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Character Health Component"));
}

void ABaseCharacter::HandleDeath()
{
	if (DeathParticles)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathParticles, GetActorLocation());
	}

	OnActorDead.Broadcast(this);
	Destroy();
}

void ABaseCharacter::Shoot()
{
	if (ProjectileClass == nullptr)
	{
		return;
	}
	
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
	ProjectileSpawnPoint->GetComponentLocation(),
	ProjectileSpawnPoint->GetComponentRotation());

	Projectile->SetOwner(this);
}

void ABaseCharacter::MeleeAttack()
{

}

UHealthComponent* ABaseCharacter::GetHealthComponent()
{
	return HealthComponent;
}