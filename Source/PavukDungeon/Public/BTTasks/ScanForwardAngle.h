// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ScanForwardAngle.generated.h"

enum class ERotationState : uint8
{
	RotateToRight,
	RotateToLeft,
	RotateToStartPosition
};

/**
 * 
 */
struct FBTScanForwardAngleNodeMemory : public FBTTaskMemory
{
	float TargetRightRotationYaw { 0.f };
	float TargetLeftRotationYaw { 0.f };
	float StartRotationYaw { 0.f };

	ERotationState RotationState { ERotationState::RotateToRight };
};

UCLASS()
class PAVUKDUNGEON_API UScanForwardAngle : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UScanForwardAngle();

	virtual uint16 GetSpecialMemorySize() const override;
	
protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 25;

	UPROPERTY(EditAnywhere)
	float YawAngleToScan = 90;

	void ResetMemoryParams(FBTScanForwardAngleNodeMemory* NodeMemory);

	float ChooseTargetRotation(FBTScanForwardAngleNodeMemory* NodeMemory);
	void SwitchToNextRotationStateOrFinish(UBehaviorTreeComponent& OwnerComp, FBTScanForwardAngleNodeMemory* NodeMemory);
};
