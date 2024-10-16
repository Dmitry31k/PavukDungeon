// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/InteractiveActors/Lever.h"

// Sets default values
ALever::ALever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeverMesh"));
	LeverMesh->SetupAttachment(BaseMesh);
	LeverMesh->SetRelativeRotation(FRotator(0.f, 0.f, -45.f));
}

// Called when the game starts or when spawned
void ALever::BeginPlay()
{
	Super::BeginPlay();
	
	StartLeverMeshRotation = LeverMesh->GetRelativeRotation();
}

void ALever::ActivateLever()
{	
	FRotator CurrentLeverMeshRotation = LeverMesh->GetRelativeRotation();
	if (CurrentLeverMeshRotation.Roll <= StartLeverMeshRotation.Roll + 90.f)
	{
		CurrentLeverMeshRotation.Roll += 90.f;
		LeverMesh->SetRelativeRotation(CurrentLeverMeshRotation);
		WasActivated = true;
	}
}