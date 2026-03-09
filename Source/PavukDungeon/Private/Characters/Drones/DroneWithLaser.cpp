// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Drones/DroneWithLaser.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/Pavuks/PlayerPavuk.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Components/GameplayComponents/HealthComponent.h"
#include "Components/OverlapTriggerComponents/TickOptimizer.h"
#include "Components/GameplayComponents/PatrollingComponent.h"

ADroneWithLaser::ADroneWithLaser()
{
    PrimaryActorTick.bCanEverTick = true;

    LaserNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LaserBeam"));
    LaserNiagaraComponent->SetupAttachment(RootComponent);

    HealthComponent->DestroyComponent();
    HealthComponent = nullptr;

    PatrollingComponent = CreateDefaultSubobject<UPatrollingComponent>(TEXT("PatrollingComponent"));

    ActiveTickZone = CreateDefaultSubobject<UTickOptimizer>(TEXT("ActiveZoneForTickFunction"));
    ActiveTickZone->SetupAttachment(RootComponent);
}

void ADroneWithLaser::BeginPlay()
{
    Super::BeginPlay();
    SetActorTickEnabled(false);
    LaserNiagaraComponent->SetVectorParameter(TEXT("Beam End"), ProjectileSpawnPoint->GetComponentLocation());
}

void ADroneWithLaser::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    LaserShoot();
    CheckIfPlayerTouchedLaser();
}

void ADroneWithLaser::LaserShoot()
{
    FVector StartDrawingLineLocation = ProjectileSpawnPoint->GetComponentLocation();
    FVector EndDrawingLineLocation = StartDrawingLineLocation + LaserLength * GetActorRightVector();

    IsBlockingLaser = GetWorld()->LineTraceSingleByChannel(LineTraceHitResult, StartDrawingLineLocation, EndDrawingLineLocation, ECollisionChannel::ECC_Pawn);

    if(IsBlockingLaser)
    {
        LaserNiagaraComponent->SetVectorParameter(TEXT("Beam End"), LineTraceHitResult.ImpactPoint);
        // NOTE: Emitter spawn rate is currently tied to frame rate.
        //       Lower FPS = fewer emitters = better performance on low-end devices.
        //       TODO: Maybe make emitter spawn independent from FPS in the future.
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), LaserFlashNiagaraSystem, LineTraceHitResult.ImpactPoint);
    }
    else
    {
        LaserNiagaraComponent->SetVectorParameter(TEXT("Beam End"), EndDrawingLineLocation);
    }    
}

void ADroneWithLaser::CheckIfPlayerTouchedLaser()
{
    PlayerPavuk = Cast<APlayerPavuk>(LineTraceHitResult.GetActor());

    if (PlayerPavuk)
    {
        UGameplayStatics::ApplyDamage(PlayerPavuk, LaserDamage, GetInstigatorController(), this, UDamageType::StaticClass());
    }
}