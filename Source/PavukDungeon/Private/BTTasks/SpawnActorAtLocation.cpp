// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/SpawnActorAtLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"

USpawnActorAtLocation::USpawnActorAtLocation()
{
    NodeName = "Spawn actor at random location from owner";
}

EBTNodeResult::Type USpawnActorAtLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    checkf(ToSpawnCharacter, TEXT("Please set 'ToSpawnCharacter' inside SpawnActorAtLocation task on %s"), *OwnerComp.GetName());

    FTimerHandle SpawnDelayTimerHandle;
    FTimerDelegate SpawnDelayTimerDelegate;

    APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();

    FVector CurrentActorLocation = OwnerPawn->GetActorLocation();
    FVector SpawnAtLocation;

    FRotator OwnerPawnRotation = OwnerPawn->GetActorRotation();

    bool bWasHit = FindPlaceForSpawn(SpawnAtLocation, CurrentActorLocation, OwnerPawn);

    if (bWasHit) return EBTNodeResult::Failed;

    UNiagaraComponent* SpawnedNiagaraSystem { nullptr };

    if (SpawnParticles)
    SpawnedNiagaraSystem = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SpawnParticles, SpawnAtLocation + FVector(0.f, 0.f, SpawnNiagaraSystemZOffset));

    TWeakObjectPtr<UBehaviorTreeComponent> OwnerCompPtr = &OwnerComp;
    SpawnDelayTimerDelegate.BindLambda([this, OwnerCompPtr, SpawnAtLocation, OwnerPawnRotation, SpawnedNiagaraSystem]()
    {
        SpawnActorAndFinishTask(OwnerCompPtr, SpawnAtLocation, OwnerPawnRotation, SpawnedNiagaraSystem);
    });

    GetWorld()->GetTimerManager().SetTimer(SpawnDelayTimerHandle, SpawnDelayTimerDelegate, SpawnDelay, false);
    return EBTNodeResult::InProgress;
}

bool USpawnActorAtLocation::FindPlaceForSpawn(FVector& SpawnAtLocation, FVector& CurrentActorLocation, APawn* OwnerPawn)
{
    FHitResult SpawnHitResult;

    FCollisionObjectQueryParams ObjectQueryParams;
    ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
    ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
    ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
    
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(OwnerPawn);    

    FCollisionShape CollisionShape = FCollisionShape::MakeBox(CollisionCheckerExtension);

    bool bWasHit { true };

    for (int32 i = 0; i <= MaxSpawnAttempts; i++)
    {
        SpawnAtLocation = CurrentActorLocation + FVector(FMath::RandRange(-MinSpawnDistFromCharacter , MinSpawnDistFromCharacter), FMath::RandRange(-MinSpawnDistFromCharacter, MinSpawnDistFromCharacter), CurrentActorLocation.Z);
        bWasHit = GetWorld()->SweepSingleByObjectType(SpawnHitResult, CurrentActorLocation, SpawnAtLocation, FQuat::Identity, ObjectQueryParams, CollisionShape, CollisionParams);

        if (FVector::Dist(CurrentActorLocation, SpawnAtLocation) >= MinSpawnDistFromCharacter && !bWasHit)
        {
            return bWasHit;
        }
    }

    UE_LOG(LogTemp, Error, TEXT("Failed to Find Place for spawning Actor"));
    return bWasHit;
}

void USpawnActorAtLocation::SpawnActorAndFinishTask(TWeakObjectPtr<UBehaviorTreeComponent> OwnerComp, FVector SpawnAtLocation, FRotator OwnerPawnRotation, UNiagaraComponent* SpawnedNiagaraSystem)
{   
    if (SpawnedNiagaraSystem) SpawnedNiagaraSystem->DestroyComponent();
    if (!OwnerComp.Get()) return;

    GetWorld()->SpawnActor<ACharacter>(ToSpawnCharacter, SpawnAtLocation, OwnerPawnRotation);
    FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
}