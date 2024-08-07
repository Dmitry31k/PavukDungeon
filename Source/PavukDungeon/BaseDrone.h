// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseDrone.generated.h"

UCLASS()
class PAVUKDUNGEON_API ABaseDrone : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseDrone();

	virtual void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent* ProjectileSpawnPoint;
	
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* DroneFan;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
