// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseActor.h"
#include "BaseInteractiveActor.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API ABaseInteractiveActor : public ABaseActor
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	virtual void AddActorIntoNotActivatedUnlockerActors();
	virtual void DeleteActorFromNotActivatedUnlockerActors();

private:

	UPROPERTY(EditAnywhere)
	FName MoverComponentTag;

	UPROPERTY()
	class UMoverComponent* UnlockerComponent;

	UPROPERTY()
	TArray<AActor*> FoundActorWithTag;
	
};
