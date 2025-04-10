// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Drones/DroneWithLaser.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/Pavuks/PlayerPavuk.h"
#include "Kismet/GameplayStatics.h"
#include "AIControllers/AIController_DroneWithLaser.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Components/HealthComponent.h"

ADroneWithLaser::ADroneWithLaser()
{
    PrimaryActorTick.bCanEverTick = true;

    LaserNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LaserBeam"));
    LaserNiagaraComponent->SetupAttachment(RootComponent);

    HealthComponent->DestroyComponent();
    HealthComponent = nullptr;
}

void ADroneWithLaser::BeginPlay()
{
    Super::BeginPlay();

    AAIController_DroneWithLaser* OwnerAIController = Cast<AAIController_DroneWithLaser>(GetController());

    SendDataIntoAIController(OwnerAIController);
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

void ADroneWithLaser::SendDataIntoAIController(AAIController_DroneWithLaser* OwnerAIController)
{
    if (OwnerAIController)
    {
        OwnerAIController->FirstMoveOffset_AIController = GetActorLocation() + FirstMoveOffset_Drone;
        OwnerAIController->SecondMoveOffset_AIController = OwnerAIController->FirstMoveOffset_AIController + SecondMoveOffset_Drone;
        OwnerAIController->ThirdtMoveOffset_AIController = OwnerAIController->SecondMoveOffset_AIController + ThirdMoveOffset_Drone;
        OwnerAIController->FourthMoveOffset_AIController = OwnerAIController->ThirdtMoveOffset_AIController + FourthMoveOffset_Drone;
        OwnerAIController->FifthMoveOffset_AIController = OwnerAIController->FourthMoveOffset_AIController + FifthMoveOffset_Drone;

        OwnerAIController->MustMoving_AIController = MustMoving_Drone;
        OwnerAIController->MustRotating_AIController = MustRotating_Drone;
        OwnerAIController->MustRotatingAndMoving_AIController = MustRotatingAndMoving_Drone;
    }
}