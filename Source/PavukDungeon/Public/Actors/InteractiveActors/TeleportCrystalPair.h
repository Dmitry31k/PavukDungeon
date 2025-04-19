// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractiveActors/BaseInteractiveActor.h"
#include "TeleportCrystalPair.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API ATeleportCrystalPair : public ABaseInteractiveActor
{
	GENERATED_BODY()

public:

	ATeleportCrystalPair();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, category = "Visual")
	UStaticMeshComponent* TeleportCrystalMesh;

	UPROPERTY(EditDefaultsOnly, category = "Visual")
	UBoxComponent* TeleportMeshTrigger;

	UFUNCTION()
	virtual void OnCrystalMeshOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY(EditAnywhere, category = "Teleport")
	FName TargetTeleportTag;

	UPROPERTY()
	TArray <AActor*> FoundActorsWithTeleportTag;

	UPROPERTY(EditDefaultsOnly, category = "Teleport")
	float TargetTeleportOffsetMin;
	UPROPERTY(EditDefaultsOnly, category = "Teleport")
	float TargetTeleportOffsetMax;

	UPROPERTY(EditDefaultsOnly, category = "Teleport")
	FVector BoxCheckerExtension = FVector(30, 30, 30);

	UPROPERTY()
	UBoxComponent* BoxTeleportChecker;

	UPROPERTY()
	AActor* PlayerActor;

	UPROPERTY(EditDefaultsOnly, category = "Teleport")
	int32 MaxTeleportTry = 100;

	void FindTeleportPlace(FVector TeleportCrystalLocation, AActor* TeleportToActor) const;
};
