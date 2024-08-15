// Fill out your copyright notice in the Description page of Project Settings.


#include "MoverComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Lever.h"
#include "PressurePlate.h"
#include "Components/BoxComponent.h"
#include "PlayerPavuk.h"

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

    StartComponentLocation = GetComponentLocation();
	StartLocation = GetOwner()->GetActorLocation();

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), UnlockerTag, FoundUnlockerActors);
	if (FoundUnlockerActors.IsValidIndex(0))
	{
		Lever = Cast<ALever>(FoundUnlockerActors[0]);
		PressurePlate = Cast<APressurePlate>(FoundUnlockerActors[0]);
	}

    OnComponentBeginOverlap.AddDynamic(this, &UMoverComponent::DestroyIfOverlapped);

	DetachFromParent();
    SetWorldLocation(StartComponentLocation);
}


// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MoveToTarget();
}

void UMoverComponent::MoveToTarget()
{
	if (CheckActor() || WasKilledAllWithTag())
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector TargetLocation = StartLocation + MoveOffset;

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

bool UMoverComponent::CheckActor()
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

bool UMoverComponent::WasKilledAllWithTag()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), ToKillTag, FoundAliveActors);

	if (FoundUnlockerActors.IsEmpty())
	{
		if(FoundAliveActors.Num() == 0)
		{
			return true;
		}
	}
	
	return false;
}

void UMoverComponent::DestroyIfOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (Cast<APlayerPavuk>(OtherActor))
    {
        DestroyComponent();
    }
}
