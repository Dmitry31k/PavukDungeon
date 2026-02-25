// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseActor.h"
#include "Interfaces/HighligningInterface.h"
#include "Interfaces/ActivatableInterface.h"
#include "BaseInteractiveActor.generated.h"

#define CUSTOM_DEPTH_HIGHLIGHT_GREEN 255

class UBoxComponent;

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API ABaseInteractiveActor : public ABaseActor, public IHighligningInterface, public IActivatableInterface
{
	GENERATED_BODY()

public:

	ABaseInteractiveActor();

	// HighligningInterface start
	virtual void HighlightObject() override;
	virtual void UnHighlightObject() override;
	// HighligningInterface end


	
	FOnActivatedSignature OnActivated;
	
	FOnDeactivatedSignature OnDeactivated;

	// ActivatableInterface start
	virtual FOnActivatedSignature& GetOnActivatedDelegate() { return OnActivated; }
	virtual FOnDeactivatedSignature& GetOnDeactivatedDelegate() { return OnDeactivated; }
	// ActivatableInterface end

protected:

	virtual void BeginPlay() override;

	//Array for meshes that have to highlight/unhighlight
	UPROPERTY()
	TArray<UMeshComponent*> ToHighlightMesh;

	//Trigger responsible for highlighting/unhighlighting meshes in ToHighlightStaticMesh and ToHighlightSkeletalMesh
	UPROPERTY(EditDefaultsOnly, category = "Visual")
	UBoxComponent* OverlapBoxHighlighterTrigger;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
