// Fill out your copyright notice in the Description page of Project Settings.

#include "Mover.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Lever.h"
#include "PressurePlate.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetOwner()->GetActorLocation();
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), UnlockerTag, FoundActors);
	if (FoundActors.IsValidIndex(0))
	{
		Lever = Cast<ALever>(FoundActors[0]);
		PressurePlate = Cast<APressurePlate>(FoundActors[0]);
	}
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MoveToTarget();
}

void UMover::MoveToTarget()
{
	if (CheckActor())
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector TargetLocation = StartLocation + MoveOffset;

		if (CurrentLocation == TargetLocation)
		{
			DestroyComponent();
		}

		FVector NewLocation = FMath::VInterpConstantTo(GetOwner()->GetActorLocation(), TargetLocation, 
		UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), MovementSpeed);

		GetOwner()->SetActorLocation(NewLocation);
	}
	else
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();

		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, StartLocation, 
    	UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), MovementSpeed);

    	GetOwner()->SetActorLocation(NewLocation);
	}
}

bool UMover::CheckActor()
{
	if (Lever)
	{
		return Lever->WasActivated;
	}
	else if (PressurePlate)
	{
		return PressurePlate->WasActivated;
	}
	
	return false;
}