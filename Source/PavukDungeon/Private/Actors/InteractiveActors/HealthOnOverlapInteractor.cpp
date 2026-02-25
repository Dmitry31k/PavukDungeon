// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractiveActors/HealthOnOverlapInteractor.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/GameplayComponents/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/DeathInterface.h"

AHealthOnOverlapInteractor::AHealthOnOverlapInteractor()
{
    MeshForActor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh for actor"));
    RootComponent = MeshForActor;

    InteractSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Health interaction trigger sphere"));
    InteractSphere->SetupAttachment(MeshForActor);

    OverlapBoxHighlighterTrigger->SetupAttachment(RootComponent);
    ToHighlightMesh.Add(MeshForActor);
}

void AHealthOnOverlapInteractor::BeginPlay()
{
    Super::BeginPlay();

    InteractSphere->OnComponentBeginOverlap.AddDynamic(this, &AHealthOnOverlapInteractor::OnTriggerBeginOverlap);
    InteractSphere->OnComponentEndOverlap.AddDynamic(this, &AHealthOnOverlapInteractor::OnTriggerEndOverlap);

    PlayerActor = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    IDeathInterface* ActorDeathInterface = Cast<IDeathInterface>(PlayerActor);
    PlayerHealthComponent = ActorDeathInterface->GetHealthComponent();
    
    checkf(PlayerHealthComponent, TEXT("PlayerHealthComponent is invalid pointer, please check PlayerPavuk class"));
}

void AHealthOnOverlapInteractor::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (PlayerActor != OtherActor)
    {
        return;
    }

    switch (InteractPolicy)
    {
        case EInteractionPolicy::InteractOnStartOverlap:
            HandlePlayerHealthChange();
        break;

        case EInteractionPolicy::InteractDuringOverlapWithTimer:
            GetWorldTimerManager().SetTimer(HealthChangeTimerHandle, this, &AHealthOnOverlapInteractor::HandlePlayerHealthChange, ChangeHealthTimer, true);
        break;

        case EInteractionPolicy::InteractAfterOverlapWithTimer:
            GetWorldTimerManager().SetTimer(HealthChangeTimerHandle, this, &AHealthOnOverlapInteractor::HandlePlayerHealthChange, ChangeHealthTimer, true);
        break;
    }

    if (DestroyPolicy == EDestroyPolicy::DestroyOnBeginOverlap)
    {
        HandleDeath();
    }
}

void AHealthOnOverlapInteractor::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (PlayerActor != OtherActor)
    {
        return;
    }

    switch (InteractPolicy)
    {
        case EInteractionPolicy::InteractOnEndOverlap:
            HandlePlayerHealthChange();
        break;

        case EInteractionPolicy::InteractDuringOverlapWithTimer:
            GetWorldTimerManager().ClearTimer(HealthChangeTimerHandle);
        break;

        case EInteractionPolicy::InteractAfterOverlapWithTimer:
            GetWorldTimerManager().SetTimer(HealthChangeClearDelayTimerHandle, this, &AHealthOnOverlapInteractor::ClearHealthChangeTimer, HealthChangeClearDelay, false);
        break;
    }

    if (DestroyPolicy == EDestroyPolicy::DestroyOnEndOverlap)
    {
        HandleDeath();
    }
}

void AHealthOnOverlapInteractor::HandlePlayerHealthChange()
{
    switch (HealthInteract)
    {
        case EHealthInteractionType::Heal:
            PlayerHealthComponent->SetClampedCurrentHealth(PlayerHealthComponent->GetCurrentHealth() + HealthChangeAmount);
        break;

        case EHealthInteractionType::Damage:
            PlayerHealthComponent->SetClampedCurrentHealth(PlayerHealthComponent->GetCurrentHealth() - HealthChangeAmount);
        break;
    }
}

void AHealthOnOverlapInteractor::HandleDeath()
{
    if (InteractPolicy == EInteractionPolicy::InteractAfterOverlapWithTimer)
    {
        this->SetActorEnableCollision(false);
        this->SetActorHiddenInGame(true);
        this->bGenerateOverlapEventsDuringLevelStreaming = false;

        GetWorldTimerManager().SetTimer(HealthChangeClearDelayTimerHandle, this, &AHealthOnOverlapInteractor::DestroyAfterDelay, HealthChangeClearDelay, false);
    }
    else
    {
        Destroy();
    }
}

void AHealthOnOverlapInteractor::DestroyAfterDelay()
{
    Destroy();
}

void AHealthOnOverlapInteractor::ClearHealthChangeTimer()
{
    GetWorldTimerManager().ClearTimer(HealthChangeTimerHandle);
}