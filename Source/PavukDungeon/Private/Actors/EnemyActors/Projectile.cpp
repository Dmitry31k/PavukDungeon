// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EnemyActors/Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	ProjectileMovementComponent->MaxSpeed = LaunchSpeed;
	ProjectileMovementComponent->InitialSpeed = LaunchSpeed;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnComponentHit);
}

void AProjectile::OnComponentHit(UPrimitiveComponent* HitComp, AActor* GotHitActor, UPrimitiveComponent* GotHitComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* ProjectileActorOwner = GetOwner();
	if (GotHitActor != ProjectileActorOwner && GotHitActor != this)
	{
		UGameplayStatics::ApplyDamage(GotHitActor, 
			Damage, 
			ProjectileActorOwner->GetInstigatorController(), 
			this, 
			UDamageType::StaticClass()
		);
	}

	Destroy();
}