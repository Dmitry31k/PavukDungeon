// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	RootComponent = ProjectileMesh;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnComponentHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveProjectile(DeltaTime);
}

void AProjectile::MoveProjectile(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = CurrentLocation + ProjectileMesh->GetForwardVector() * LaunchSpeed * DeltaTime;

	SetActorLocation(TargetLocation, true);
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