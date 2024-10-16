// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ScanForwardAngle.generated.h"

/**
 * 
 */
UCLASS()
class PAVUKDUNGEON_API UBTTask_ScanForwardAngle : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_ScanForwardAngle();
	
protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 25;

	UPROPERTY(EditAnywhere)
	float YawAngleValue = 90;

	UPROPERTY()
	class AAIController* OwnerController;

	UPROPERTY()
	class APawn* OwnerPawn;

	FRotator CurrentRotation;
	FRotator TargetRotation;
	FRotator StartRotation;

	bool IsWasTurnRight = false;
	bool IsWasScannedFullAngle = false;

	void ScanForwardAngle(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds);
	void ReturnToStartPosition(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds);
	
};
