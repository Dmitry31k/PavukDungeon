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

	if (ToKillActorTagName != NAME_None)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsWithTag(this, ToKillActorTagName, FoundActors);

		if (FoundActors.Num() > 0)
		{
			for (AActor* Actor : FoundActors)
			{
				if (IDeathInterface* DeathInterface = Cast<IDeathInterface>(Actor))
				{
					FoundToKillActors.AddUnique(Actor);
					DeathInterface->GetOnActorDeadDelegate().AddDynamic(this, &UMoverComponent::HandleDeathOrActivationActor);
				}
			}
		}
	}

	if (ToActivateActorTagName != NAME_None)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsWithTag(this, ToActivateActorTagName, FoundActors);

		if (FoundActors.Num() > 0)
		{
			for (AActor* Actor : FoundActors)
			{
				if (IActivatableInterface* ActivatableInterface = Cast<IActivatableInterface>(Actor))
				{
					FoundToActivateActors.AddUnique(Actor);
					ActivatableInterface->GetOnActivatedDelegate().AddDynamic(this, &UMoverComponent::HandleDeathOrActivationActor);
					ActivatableInterface->GetOnDeactivatedDelegate().AddDynamic(this, &UMoverComponent::HandleDeactivationActor);
				}
			}
		}
	}
}

void UMoverComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bMoveToTargetLocation)
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector NewLocation = FMath::VInterpConstantTo(GetOwner()->GetActorLocation(), 
			TargetLocation, 
			DeltaTime,
			MovementSpeed
		);

		GetOwner()->SetActorLocation(NewLocation);

		if (CurrentLocation == TargetLocation)
		{
			SetComponentTickEnabled(false);
		}
	}
	else
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation,
			StartLocation, 
    		DeltaTime,
			MovementSpeed
		);

    	GetOwner()->SetActorLocation(NewLocation);

		if (CurrentLocation == StartLocation)
		{
			SetComponentTickEnabled(false);
		}
	}

	if (bPrintTickLog)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor %s is ticking"), *GetNameSafe(this));
	}
}

void UMoverComponent::HandleDeathOrActivationActor(AActor* DeadOrActivatedActor)
{
	FoundToKillActors.Remove(DeadOrActivatedActor);
	FoundToActivateActors.Remove(DeadOrActivatedActor);
	

	if (FoundToKillActors.Num() == 0 && FoundToActivateActors.Num() == 0)
	{
		bMoveToTargetLocation = true;
		SetComponentTickEnabled(true);
	}
}
void UMoverComponent::HandleDeactivationActor(AActor* DeactivatedActor)
{

	FoundToActivateActors.Add(DeactivatedActor);
	bMoveToTargetLocation = false;
	SetComponentTickEnabled(true);
}
	