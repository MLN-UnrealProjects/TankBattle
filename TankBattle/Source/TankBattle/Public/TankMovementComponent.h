// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * Responsible for driving the tank tracks
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnClockwise(float Throw);
	UFUNCTION(Category = Setup, BlueprintCallable)
	void Initialize(UTankTrack* LeftTrack, UTankTrack* RightTrack);

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
