// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractiveActor.h"
#include "Lever.generated.h"

UCLASS()
class PAVUKDUNGEON_API ALever : public ABaseInteractiveActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALever();

	virtual void ActivateLever();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* LeverMesh;

	FRotator StartLeverMeshRotation;
};
