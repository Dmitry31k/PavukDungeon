// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPavuk.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Lever.h"
#include "Projectile.h"

APlayerPavuk::APlayerPavuk()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

    Arm->SetupAttachment(RootComponent);
    Camera->SetupAttachment(Arm);
}

void APlayerPavuk::BeginPlay()
{
    Super::BeginPlay();
	Controller = Cast<APlayerController>(GetController());    
}

// Called every frame
void APlayerPavuk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);    
    
    DrawDebugSphere(GetWorld(), CursorHitResult.ImpactPoint, 25, 32, FColor::Blue);
}

// Called to bind functionality to input
void APlayerPavuk::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerPavuk::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("TurnRight"), this, &APlayerPavuk::TurnRight);
    PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &ACharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &APlayerPavuk::Interact);
    PlayerInputComponent->BindAction(TEXT("Grab"), IE_Pressed, this, &APlayerPavuk::Grab);
    PlayerInputComponent->BindAction(TEXT("Grab"), IE_Released, this, &APlayerPavuk::Release);
    PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &APlayerPavuk::Shoot);
}

void APlayerPavuk::MoveForward(float Scale)
{
    AddMovementInput(GetActorForwardVector() * Scale);
}

void APlayerPavuk::TurnRight(float Scale)
{
    AddMovementInput(GetActorRightVector() * Scale);
}

void APlayerPavuk::Interact()
{
    if (Controller)
    {
        Controller->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHitResult);

        FHitResult InteractHit;
    
        if (FVector::Dist(GetActorLocation(), CursorHitResult.ImpactPoint) <= InteractDistance)
        {
            GetWorld()->SweepSingleByChannel(InteractHit, 
                GetActorLocation(), 
                CursorHitResult.ImpactPoint, 
                FQuat::Identity, 
                ECC_GameTraceChannel1, 
                FCollisionShape::MakeSphere(25)
            );

            ActivateLever(CursorHitResult);
        }
    }    
}

void APlayerPavuk::ActivateLever(FHitResult HitResultUnderCursor)
{
    Lever = Cast<ALever>(HitResultUnderCursor.GetActor());
    if (Lever)
    {        
        Lever->ActivateLever();
    }
}

void APlayerPavuk::Grab()
{
    Super::Grab();
}

void APlayerPavuk::Release()
{
    Super::Release();
}

void APlayerPavuk::PavukDied()
{
    Super::PavukDied();

    if (Controller)
    {
        SetActorHiddenInGame(true);
        DisableInput(Controller);
        IsAlive = false;
    }
}

void APlayerPavuk::Shoot()
{
    Super::Shoot();
}