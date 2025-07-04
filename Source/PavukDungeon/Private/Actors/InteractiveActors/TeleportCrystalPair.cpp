// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractiveActors/TeleportCrystalPair.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ATeleportCrystalPair::ATeleportCrystalPair()
{
    TeleportCrystalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh to teleport"));
    TeleportMeshTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger for teleport"));

    RootComponent = TeleportCrystalMesh;
    OverlapBoxHighlighterTrigger->SetupAttachment(RootComponent);
    TeleportMeshTrigger->SetupAttachment(RootComponent);

    ToHighlightStaticMesh.Add(TeleportCrystalMesh);

    BoxTeleportChecker = CreateDefaultSubobject<UBoxComponent>(TEXT("Simple cheker for teleport location"));
    BoxTeleportChecker->SetBoxExtent(BoxCheckerExtension);
}

void ATeleportCrystalPair::BeginPlay()
{
    Super::BeginPlay();

    TeleportMeshTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATeleportCrystalPair::OnCrystalMeshOverlapped);
    
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), TargetTeleportTag, FoundActorsWithTeleportTag);
    PlayerActor = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void ATeleportCrystalPair::OnCrystalMeshOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (FoundActorsWithTeleportTag.Num() > 0 && OtherActor == PlayerActor)
    {
        int TeleportToActor = FMath::RandRange(0, FoundActorsWithTeleportTag.Num() - 1);

        FVector TeleportCrystalLocation = FoundActorsWithTeleportTag[TeleportToActor]->GetActorLocation();

        FindTeleportPlace(TeleportCrystalLocation, FoundActorsWithTeleportTag[TeleportToActor]);
    }
}

void ATeleportCrystalPair::FindTeleportPlace(FVector TeleportCrystalLocation, AActor* TeleportToActor) const
{
    for (size_t i = 0; i < MaxTeleportTry; i++)
    {
        FVector TeleportLocation;

        TeleportLocation.X = TeleportCrystalLocation.X + FMath::RandRange(-TargetTeleportOffsetMax, TargetTeleportOffsetMax);
        TeleportLocation.Y = TeleportCrystalLocation.Y + FMath::RandRange(-TargetTeleportOffsetMax, TargetTeleportOffsetMax);
        TeleportLocation.Z = TeleportCrystalLocation.Z;

        if (FVector::Dist(TeleportLocation, TeleportCrystalLocation) >= TargetTeleportOffsetMin)
        {
            TArray<AActor*> CheckerOverlapActors;

            BoxTeleportChecker->SetWorldLocation(TeleportLocation);

            BoxTeleportChecker->GetOverlappingActors(CheckerOverlapActors);
            CheckerOverlapActors.Remove(TeleportToActor);

            if (CheckerOverlapActors.IsEmpty())
            {
                PlayerActor->SetActorLocation(TeleportLocation);
                break;
            }
        }
    }
}