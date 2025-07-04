// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseActor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Components/GameplayComponents/HealthComponent.h"

// Sets default values
ABaseActor::ABaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseActor::HandleDeath()
{
	if (DeathParticles)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathParticles, GetActorLocation());
	}

	Destroy();
}

UHealthComponent* ABaseActor::GetHealthComponent()
{
	//Not used here
	return nullptr;
}