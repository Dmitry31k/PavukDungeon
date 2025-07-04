// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseActor.h"
#include "Interfaces/HighligningInterface.h"
#include "BaseInteractiveActor.generated.h"

#define CUSTOM_DEPTH_HIGHLIGHT_GREEN 255

class UBoxComponent;

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API ABaseInteractiveActor : public ABaseActor, public IHighligningInterface
{
	GENERATED_BODY()

public:

	ABaseInteractiveActor();

	virtual void HighlightObject() override;
	virtual void UnHighlightObject() override;

protected:

	virtual void BeginPlay() override;

	virtual void AddActorIntoNotActivatedUnlockerActors();
	virtual void DeleteActorFromNotActivatedUnlockerActors();

	//Array for static meshes that have to highlight/unhighlight
	UPROPERTY()
	TArray<UStaticMeshComponent*> ToHighlightStaticMesh;
	//Array for skeletal meshes that have to highlight/unhighlight
	UPROPERTY()
	TArray<USkeletalMeshComponent*> ToHighlightSkeletalMesh;

	//Trigger responsible for highlighting/unhighlighting meshes in ToHighlightStaticMesh and ToHighlightSkeletalMesh
	UPROPERTY(EditDefaultsOnly, category = "Visual")
	UBoxComponent* OverlapBoxHighlighterTrigger;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	UPROPERTY(EditAnywhere)
	FName MoverComponentTag;

	UPROPERTY()
	class UMoverComponent* UnlockerComponent;

	UPROPERTY()
	TArray<AActor*> FoundActorWithTag;
};
