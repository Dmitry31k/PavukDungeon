// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GameplayComponents/MoverComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/DeathInterface.h"
#include "Interfaces/ActivatableInterface.h"

// Sets default values for this component's properties
UMoverComponent::UMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	// ...
}

// Called when the game starts
void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetOwner()->GetActorLocation();
	TargetLocation = StartLocation + MoveOffset;

	StartRotation = GetOwner()->GetActorRotation();
	TargetRotation = StartRotation + RotationOffset;

	InitArrayToCallbacks();
	BindCallbacksToTaggedActors();
}

void UMoverComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MoveOwner(DeltaTime);
}

void UMoverComponent::MoveOwner(float DeltaTime)
{
	if (bMoveToDestination)
	{
		SetOwnerLocationAndRotation(TargetLocation, TargetRotation, DeltaTime);

		if (GetOwner()->GetActorLocation().Equals(TargetLocation, 1.f) && 
			GetOwner()->GetActorRotation().Equals(TargetRotation, 1.f)
		)
		{
			SetComponentTickEnabled(false);
		}
	}
	else
	{
		SetOwnerLocationAndRotation(StartLocation, StartRotation, DeltaTime);

		if (GetOwner()->GetActorLocation().Equals(StartLocation, 1.f) &&
			GetOwner()->GetActorRotation().Equals(StartRotation, 1.f)
		)
		{
			SetComponentTickEnabled(false);
		}
	}

	if (bPrintTickLog)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor %s is ticking"), *GetNameSafe(this));
	}
}

void UMoverComponent::SetOwnerLocationAndRotation(const FVector& DestinationLocation, const FRotator& DestinationRotation, const float& DeltaTime)
{
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation,
		DestinationLocation, 
    	DeltaTime,
		MovementSpeed
	);

	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation,
		DestinationRotation,
		DeltaTime,
		RotationSpeed
	);

	GetOwner()->SetActorLocation(NewLocation);
	GetOwner()->SetActorRotation(NewRotation);
}

void UMoverComponent::BindCallbacksToTaggedActors()
{
	for (auto& Pair : ArrayToCallbacks)
	{
		if (Pair.Key != NAME_None)
		{
			TArray<AActor*> FoundActors;
			UGameplayStatics::GetAllActorsWithTag(this, Pair.Key, FoundActors);

			for (AActor* Actor : FoundActors)
			{
				Pair.Value(Actor);
			}
		}		
	}
}

void UMoverComponent::InitArrayToCallbacks()
{
	ArrayToCallbacks.Add(
		ToKillActorTagName,
		[this](AActor* Actor)
		{
			if (IDeathInterface* DeathInterface = Cast<IDeathInterface>(Actor))
			{
				FoundToKillActors.AddUnique(Actor);
				DeathInterface->GetOnActorDeadDelegate().AddDynamic(this, &UMoverComponent::HandleDeathOrActivationActor);
			}
		}
	);

	ArrayToCallbacks.Add(
		ToActivateActorTagName,
		[this](AActor* Actor)
		{
			if (IActivatableInterface* ActivatableInterface = Cast<IActivatableInterface>(Actor))
			{
				FoundToActivateActors.AddUnique(Actor);
				ActivatableInterface->GetOnActivatedDelegate().AddDynamic(this, &UMoverComponent::HandleDeathOrActivationActor);
				ActivatableInterface->GetOnDeactivatedDelegate().AddDynamic(this, &UMoverComponent::HandleDeactivationActor);
			}
		}
	);
}

void UMoverComponent::HandleDeathOrActivationActor(AActor* DeadOrActivatedActor)
{
	FoundToKillActors.Remove(DeadOrActivatedActor);
	FoundToActivateActors.Remove(DeadOrActivatedActor);
	
	if (FoundToKillActors.Num() == 0 && FoundToActivateActors.Num() == 0)
	{
		bMoveToDestination = true;

		if (bSmoothMovement)
		{
			SetComponentTickEnabled(true);
		}
		else
		{
			GetOwner()->SetActorLocation(TargetLocation);
			GetOwner()->SetActorRotation(TargetRotation);
		}
	}
}
void UMoverComponent::HandleDeactivationActor(AActor* DeactivatedActor)
{
	FoundToActivateActors.Add(DeactivatedActor);
	bMoveToDestination = false;

	if (bSmoothMovement)
	{
		SetComponentTickEnabled(true);
	}
	else
	{
		GetOwner()->SetActorLocation(StartLocation);
		GetOwner()->SetActorRotation(StartRotation);
	}
}