// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/EnemyActors/BaseEnemyActor.h"
#include "EnemyActorWithOverlapBoxComp.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API AEnemyActorWithOverlapBoxComp : public ABaseEnemyActor
{
	GENERATED_BODY()

public:

	AEnemyActorWithOverlapBoxComp();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, category = "combat")
	class UBoxComponent* TriggerBoxComponent;

	UFUNCTION()
	virtual void TriggerBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void TriggerBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
