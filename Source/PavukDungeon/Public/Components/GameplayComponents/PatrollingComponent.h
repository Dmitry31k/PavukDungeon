// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrollingComponent.generated.h"

class ATargetPoint;

UENUM(BlueprintType)
enum class EPatrollingType : uint8
{
	PatrolOnly,
	PatrolAndRotate,
	RotateOnly,
	DoNothing
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PAVUKDUNGEON_API UPatrollingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPatrollingComponent();

	TArray<AActor*> GetPatrolPts() const { return PatrollingPoints; }
	EPatrollingType GetPatrolType() const { return PatrollingType; }

private:

	UPROPERTY(EditAnywhere)
	TArray<AActor*> PatrollingPoints;

	UPROPERTY(EditAnywhere)
	EPatrollingType PatrollingType { EPatrollingType::DoNothing };
};
