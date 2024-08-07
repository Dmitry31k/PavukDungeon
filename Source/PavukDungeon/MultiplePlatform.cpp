// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplePlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Timermanager.h"

// Sets default values
AMultiplePlatform::AMultiplePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = PlatformMesh;
}

// Called when the game starts or when spawned
void AMultiplePlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	if (TimerDissapear > 0)
	{
		GetWorldTimerManager().SetTimer(EnableTimer, this, &AMultiplePlatform::PlatformDisable, TimerApear, false);
		GetWorldTimerManager().SetTimer(MainCount, this, &AMultiplePlatform::PlatformEnable, TimerDissapear + TimerApear, true);
	}
}

// Called every frame
void AMultiplePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (MovingDistance != FVector::ZeroVector)
	{
		SetPlatformNewLocation(DeltaTime);
	}
}

void AMultiplePlatform::PlatformDisable()
{
	PlatformMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	PlatformMesh->SetHiddenInGame(true);
}
void AMultiplePlatform::PlatformEnable()
{
	PlatformMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	PlatformMesh->SetHiddenInGame(false);
	GetWorldTimerManager().SetTimer(EnableTimer, this, &AMultiplePlatform::PlatformDisable, TimerApear, false);
}

void AMultiplePlatform::SetPlatformNewLocation(float DeltaTime)
{
	//Calculating point at which platform have to be
	FVector TargetLocation = StartLocation + MovingDistance;
	FVector SetLocation = GetActorLocation() + MovingSpeed * DeltaTime;

	if (FVector::Dist(StartLocation, SetLocation) < FVector::Dist(StartLocation, TargetLocation))
	{
		SetActorLocation(SetLocation);
		DistanceMoved = FVector::Dist(StartLocation, GetActorLocation());
	}
	else
	{
		SetActorLocation(TargetLocation);
		MovingDistance = -MovingDistance;
		MovingSpeed = -MovingSpeed;
		StartLocation = GetActorLocation();
		DistanceMoved = 0;
	}
}
