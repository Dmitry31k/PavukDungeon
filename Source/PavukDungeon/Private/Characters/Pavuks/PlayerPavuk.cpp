// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Pavuks/PlayerPavuk.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Actors/InteractiveActors/Lever.h"
#include "Gamemodes/DefaultGamemode.h"
#include "PlayerControllers/DefaultPlayerController.h"
#include "UI/HUD/BaseHUD.h"

APlayerPavuk::APlayerPavuk()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

    Arm->SetupAttachment(RootComponent);
    Camera->SetupAttachment(Arm);
}

void APlayerPavuk::BeginPlay()
{
    Super::BeginPlay();
    
	DefaultPlayerController = Cast<ADefaultPlayerController>(GetController());
    
    if (DefaultPlayerController)
    {
        InitOverlayOnHUD(DefaultPlayerController, HealthComponent);
    }
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
    PlayerInputComponent->BindAction(TEXT("MeleeAttack"), IE_Pressed, this, &APlayerPavuk::MeleeAttack);
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
    FHitResult InteractHit;

    bool WasSuccess = GetWorld()->SweepSingleByChannel(InteractHit,
        GetActorLocation(),
        GetActorForwardVector() * InteractDistance,
        FQuat::Identity,
        ECC_GameTraceChannel1, 
        FCollisionShape::MakeSphere(200)
    );
    
    if (WasSuccess)
    {            
        ActivateLever(InteractHit);
    }
}

void APlayerPavuk::ActivateLever(FHitResult ActivateLeverHitResult)
{
    Lever = Cast<ALever>(ActivateLeverHitResult.GetActor());
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

void APlayerPavuk::CharacterDied()
{
    Super::CharacterDied();

    if (DefaultPlayerController)
    {
        ADefaultGamemode* CurrentGameMode = GetWorld()->GetAuthGameMode<ADefaultGamemode>();
        if (CurrentGameMode)
        {
            CurrentGameMode->PlayerDied(DefaultPlayerController);
        }

        DetachFromControllerPendingDestroy();
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void APlayerPavuk::Shoot()
{
    // Prevent spamming range attacks: call the base class shoot only if shooting is allowed.
    if (CanShoot)
    {
        Super::Shoot();

        CanShoot = false;
        GetWorldTimerManager().SetTimer(SetShootTimerHandle, this, &APlayerPavuk::SetCanShootTrue, RechargingShootSpeed, false);
    }
}

void APlayerPavuk::SetCanShootTrue()
{
	CanShoot = true;
}
void APlayerPavuk::SetWasMeleeDamageFalse()
{
	WasMeleeDamage = false;
}

void APlayerPavuk::MeleeAttack()
{
    // Prevent spamming melee attacks: call the base class attack only if melee damage is allowed.
    if (!WasMeleeDamage)
    {
        Super::MeleeAttack();

        WasMeleeDamage = true;
        GetWorldTimerManager().SetTimer(SetWasMeleeDamagedTimerHandle, this, &APlayerPavuk::SetWasMeleeDamageFalse, RechargingMeleeDamageSpeed, false);
    }
}

void APlayerPavuk::InitOverlayOnHUD(APlayerController* InPlayerController, UHealthComponent* InHealthComponent)
{
    ABaseHUD* PlayerPavukHUD = Cast<ABaseHUD>(InPlayerController->GetHUD());

    if (PlayerPavukHUD)
    {
        PlayerPavukHUD->InitOverlay(InPlayerController, InHealthComponent);
    }
}