// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneWithLaser.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerPavuk.h"
#include "Kismet/GameplayStatics.h"

ADroneWithLaser::ADroneWithLaser()
{

}

void ADroneWithLaser::BeginPlay()
{
    Super::BeginPlay();


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
    FVector EndDrawingLineLocation = StartDrawingLineLocation + LaserLength * GetActorForwardVector();

    GetWorld()->LineTraceSingleByChannel(LineTraceHitResult, StartDrawingLineLocation, EndDrawingLineLocation, ECollisionChannel::ECC_Pawn);

    DrawDebugLine(GetWorld(), StartDrawingLineLocation, EndDrawingLineLocation, FColor::Red);
}

void ADroneWithLaser::CheckIfPlayerTouchedLaser()
{
    PlayerPavuk = Cast<APlayerPavuk>(LineTraceHitResult.GetActor());

    if (PlayerPavuk)
    {
        UGameplayStatics::ApplyDamage(PlayerPavuk, LaserDamage, GetInstigatorController(), this, UDamageType::StaticClass());
    }
}