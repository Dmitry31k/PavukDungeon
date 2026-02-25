// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EnemyActors/BaseEnemyActor.h"
#include "Components/GameplayComponents/HealthComponent.h"
#include "Components/GameplayComponents/MoverComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/EnemyActors/Projectile.h"

ABaseEnemyActor::ABaseEnemyActor()
{
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Actor Health Component"));
}

void ABaseEnemyActor::BeginPlay()
{
    Super::BeginPlay();


}

void ABaseEnemyActor::HandleDeath()
{
    Super::HandleDeath();
    
    OnActorDead.Broadcast(this);
}

UHealthComponent* ABaseEnemyActor::GetHealthComponent()
{
    return HealthComponent;
}

void ABaseEnemyActor::Shoot()
{
    AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, 
	ProjectileSpawnPoint->GetComponentLocation(), 
	ProjectileSpawnPoint->GetComponentRotation()
		);

	Projectile->SetOwner(this);
}