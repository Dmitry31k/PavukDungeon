// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Drones/BaseDrone.h"
#include "Actors/EnemyActors/Projectile.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ABaseDrone::ABaseDrone()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DroneFan = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Drone fan"));
	DroneFan->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Drone projectile spawnpoint"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
}