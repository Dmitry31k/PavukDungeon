// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/EnemyActors/BaseEnemyActor.h"
#include "Projectile.generated.h"

UCLASS()
class PAVUKDUNGEON_API AProjectile : public ABaseEnemyActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void MoveProjectile(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* ProjectileMesh;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComp, AActor* GotHitActor, UPrimitiveComponent* GotHitComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, category = "combat")
	float LaunchSpeed = 1000;

	UPROPERTY(EditDefaultsOnly, category = "combat")
	float Damage = 25;
};
