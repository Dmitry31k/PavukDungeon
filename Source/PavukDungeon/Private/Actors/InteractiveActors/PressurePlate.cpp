// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractiveActors/PressurePlate.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = PlateMesh;
	CollisionBox->SetupAttachment(PlateMesh);
	OverlapBoxHighlighterTrigger->SetupAttachment(PlateMesh);

	ToHighlightMesh.Add(PlateMesh);
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::StartOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::EndOverlap);
}

void APressurePlate::StartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		OnActivated.Broadcast(this);
		OverlappingActors.AddUnique(OtherActor);
	}
}

void APressurePlate::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlappingActors.Remove(OtherActor);
	
	if (OtherActor != this && OverlappingActors.Num() == 0)
	{
		OnDeactivated.Broadcast(this);
	}
}