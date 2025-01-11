// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MoverComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMoverComponent::UMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetOwner()->GetActorLocation();
	TargetLocation = StartLocation + MoveOffset;
}

// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UMoverComponent::MoveToTargetLocation()
{
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector NewLocation = FMath::VInterpConstantTo(GetOwner()->GetActorLocation(), TargetLocation, 
	UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), MovementSpeed);

	GetOwner()->SetActorLocation(NewLocation);

	if (CurrentLocation != TargetLocation && (NotActivatedUnlockerActors.Num() == 0 && AliveActors.Num() == 0))
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UMoverComponent::MoveToTargetLocation);
	}
}

void UMoverComponent::MoveToStartLocation()
{
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, StartLocation, 
    UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), MovementSpeed);

    GetOwner()->SetActorLocation(NewLocation);

	if (CurrentLocation != StartLocation  && (NotActivatedUnlockerActors.Num() > 0 || AliveActors.Num() > 0))
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UMoverComponent::MoveToStartLocation);
	}
}