// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Actors/EnemyActors/Projectile.h"
#include "Characters/Pavuks/PlayerPavuk.h"
#include "Components/GameplayComponents/HealthComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Character Health Component"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	OnTakeAnyDamage.AddDynamic(this, &ABaseCharacter::WasHitByPlayer);
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

void ABaseCharacter::WasHitByPlayer(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Cast<APlayerPavuk>(DamageCauser->GetOwner()) || Cast<APlayerPavuk>(DamageCauser))
	{
		IsWasHitByPlayer = true;
	}
}

UHealthComponent* ABaseCharacter::GetHealthComponent()
{
	return HealthComponent;
}