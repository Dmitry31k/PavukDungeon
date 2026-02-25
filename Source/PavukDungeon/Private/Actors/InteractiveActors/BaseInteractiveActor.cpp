// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractiveActors/BaseInteractiveActor.h"
#include "Components/GameplayComponents/MoverComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Characters/Pavuks/PlayerPavuk.h"

ABaseInteractiveActor::ABaseInteractiveActor()
{
    OverlapBoxHighlighterTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Highlight/unhighlight trigger box"));
    OverlapBoxHighlighterTrigger->ComponentTags.Add("IgnoreDamage");
}

void ABaseInteractiveActor::BeginPlay()
{
    Super::BeginPlay();

    OverlapBoxHighlighterTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseInteractiveActor::OnOverlapBegin);
    OverlapBoxHighlighterTrigger->OnComponentEndOverlap.AddDynamic(this, &ABaseInteractiveActor::OnOverlapEnd);
}

void ABaseInteractiveActor::HighlightObject()
{
    if (ToHighlightMesh.Num() > 0)
    {
        for (UMeshComponent* Mesh : ToHighlightMesh)
        {
            Mesh->SetRenderCustomDepth(true);
            Mesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_HIGHLIGHT_GREEN);
        }
    }
}

void ABaseInteractiveActor::UnHighlightObject()
{
    if (ToHighlightMesh.Num() > 0)
    {
        for (UMeshComponent* Mesh : ToHighlightMesh)
        {
            Mesh->SetRenderCustomDepth(false);
            Mesh->SetCustomDepthStencilValue(0);
        }
    }
}

void ABaseInteractiveActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (Cast<APlayerPavuk>(OtherActor))
    {
        HighlightObject();
    }
}

void ABaseInteractiveActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (Cast<APlayerPavuk>(OtherActor))
    {
        UnHighlightObject();
    }
}