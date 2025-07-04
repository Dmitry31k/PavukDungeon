// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/BTTask_SpawnActorAtLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"

UBTTask_SpawnActorAtLocation::UBTTask_SpawnActorAtLocation()
{
    NodeName = "Spawn actor at random location from owner";
}

EBTNodeResult::Type UBTTask_SpawnActorAtLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (ToSpawnCharacter == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    FTimerHandle SpawnDelayTimerHandle;
    FTimerDelegate SpawnDelayTimerDelegate;

    APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
    FVector CurrentActorLocation = OwnerPawn->GetActorLocation();
    FVector SpawnAtLocation;
    FRotator OwnerPawnRotation = OwnerPawn->GetActorRotation();

    FindPlaceForSpawn(SpawnAtLocation, CurrentActorLocation, OwnerPawn);

    if (!WasHit)
    {   
        if (SpawnParticles)
        {
            UNiagaraComponent* SpawnedNiagaraSystem = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SpawnParticles, SpawnAtLocation + FVector(0.f, 0.f, SpawnNiagaraSystemZOffset));
            SpawnDelayTimerDelegate.BindLambda([this, &OwnerComp, SpawnAtLocation, OwnerPawnRotation, SpawnedNiagaraSystem]()
            {
                SpawnActorAndFinishTask(&OwnerComp, SpawnAtLocation, OwnerPawnRotation, SpawnedNiagaraSystem);
            });
        }
        else
        {
            SpawnDelayTimerDelegate.BindLambda([this, &OwnerComp, SpawnAtLocation, OwnerPawnRotation]()
            {
                SpawnActorAndFinishTask(&OwnerComp, SpawnAtLocation, OwnerPawnRotation);
            });
        }

        GetWorld()->GetTimerManager().SetTimer(SpawnDelayTimerHandle, SpawnDelayTimerDelegate, SpawnDelay, false);

        return EBTNodeResult::InProgress;
    }

    return EBTNodeResult::Failed;
}

void UBTTask_SpawnActorAtLocation::FindPlaceForSpawn(FVector& SpawnAtLocation, FVector& CurrentActorLocation, APawn* OwnerPawn)
{
    FHitResult SpawnHitResult;

    FCollisionObjectQueryParams ObjectQueryParams;
    ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
    ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
    ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
    
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(OwnerPawn);    

    FCollisionShape CollisionShape = FCollisionShape::MakeBox(CollisionCheckerExtension);

    SpawnAtLocation = CurrentActorLocation + FVector(FMath::RandRange(-MinSpawnDistFromCharacter * SpawnMultiplyer, MinSpawnDistFromCharacter * SpawnMultiplyer), FMath::RandRange(-MinSpawnDistFromCharacter * SpawnMultiplyer, MinSpawnDistFromCharacter * SpawnMultiplyer), 0.f);

    WasHit = GetWorld()->SweepSingleByObjectType(SpawnHitResult, CurrentActorLocation, SpawnAtLocation, FQuat::Identity, ObjectQueryParams, CollisionShape, CollisionParams);

    int Count = 0;

    while (WasHit && Count < MaxTryToSpawn && FVector::Dist(CurrentActorLocation, SpawnAtLocation) >= MinSpawnDistFromCharacter)
    {        
        SpawnAtLocation = CurrentActorLocation + FVector(FMath::RandRange(-MinSpawnDistFromCharacter * SpawnMultiplyer, MinSpawnDistFromCharacter * SpawnMultiplyer), FMath::RandRange(-MinSpawnDistFromCharacter * SpawnMultiplyer, MinSpawnDistFromCharacter * SpawnMultiplyer), 0.f);

        WasHit = GetWorld()->SweepSingleByObjectType(SpawnHitResult, CurrentActorLocation, SpawnAtLocation, FQuat::Identity, ObjectQueryParams, CollisionShape, CollisionParams);
        
        if (FVector::Dist(CurrentActorLocation, SpawnAtLocation) <= MinSpawnDistFromCharacter)
        {
            SpawnAtLocation += FVector(FMath::RandRange(-MinSpawnDistFromCharacter, MinSpawnDistFromCharacter), FMath::RandRange(-MinSpawnDistFromCharacter, MinSpawnDistFromCharacter), 0.f);
            WasHit = GetWorld()->SweepSingleByObjectType(SpawnHitResult, CurrentActorLocation, SpawnAtLocation, FQuat::Identity, ObjectQueryParams, CollisionShape, CollisionParams);
        }

        Count++;
    }
}

void UBTTask_SpawnActorAtLocation::SpawnActorAndFinishTask(UBehaviorTreeComponent* OwnerComp, FVector SpawnAtLocation, FRotator OwnerPawnRotation, UNiagaraComponent* SpawnedNiagaraSystem)
{   
    if (SpawnedNiagaraSystem)
    {
        SpawnedNiagaraSystem->DestroyComponent();
    }

    GetWorld()->SpawnActor<ACharacter>(ToSpawnCharacter, SpawnAtLocation, OwnerPawnRotation);
    FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
}