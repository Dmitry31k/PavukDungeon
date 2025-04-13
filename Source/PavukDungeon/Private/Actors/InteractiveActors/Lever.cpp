// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/InteractiveActors/Lever.h"
#include "Components/BoxComponent.h"

// Sets default values
ALever::ALever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeverMesh"));
	LeverMesh->SetupAttachment(BaseMesh);
	LeverMesh->SetRelativeRotation(FRotator(0.f, 0.f, -45.f));

	OverlapBoxTrigger->SetupAttachment(BaseMesh);

	ToHighlightStaticMesh.Add(BaseMesh);
	ToHighlightStaticMesh.Add(LeverMesh);
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
		DeleteActorFromNotActivatedUnlockerActors();
	}
}