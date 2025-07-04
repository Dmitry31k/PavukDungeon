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

    if (!MoverComponentTag.IsNone())
    {
        UGameplayStatics::GetAllActorsWithTag(GetWorld(), MoverComponentTag, FoundActorWithTag);

        if (FoundActorWithTag.Num() > 0)
        {
            UnlockerComponent = Cast<UMoverComponent>(FoundActorWithTag[0]->FindComponentByClass<UMoverComponent>());
        }

        AddActorIntoNotActivatedUnlockerActors();
    }

    OverlapBoxHighlighterTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseInteractiveActor::OnOverlapBegin);
    OverlapBoxHighlighterTrigger->OnComponentEndOverlap.AddDynamic(this, &ABaseInteractiveActor::OnOverlapEnd);
}

void ABaseInteractiveActor::AddActorIntoNotActivatedUnlockerActors()
{
    if (!UnlockerComponent)
    {
        return;
    }
    UnlockerComponent->NotActivatedUnlockerActors.Add(this);
    UnlockerComponent->MoveToStartLocation();
}

void ABaseInteractiveActor::DeleteActorFromNotActivatedUnlockerActors()
{
    if (!UnlockerComponent)
    {
        return;
    }
    UnlockerComponent->NotActivatedUnlockerActors.Remove(this);
    UnlockerComponent->MoveToTargetLocation();
}

void ABaseInteractiveActor::HighlightObject()
{
    if (ToHighlightStaticMesh.Num() > 0)
    {
        for (auto Mesh : ToHighlightStaticMesh)
        {
            Mesh->SetRenderCustomDepth(true);
            Mesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_HIGHLIGHT_GREEN);
        }
    }
    else if (ToHighlightSkeletalMesh.Num() > 0)
    {
        for (auto Mesh : ToHighlightSkeletalMesh)
        {
            Mesh->SetRenderCustomDepth(true);
            Mesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_HIGHLIGHT_GREEN);
        }
    }
}

void ABaseInteractiveActor::UnHighlightObject()
{
    if (ToHighlightStaticMesh.Num() > 0)
    {
        for (auto Mesh : ToHighlightStaticMesh)
        {
            Mesh->SetRenderCustomDepth(false);
            Mesh->SetCustomDepthStencilValue(0);
        }
    }
    else if (ToHighlightSkeletalMesh.Num() > 0)
    {
        for (auto Mesh : ToHighlightSkeletalMesh)
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