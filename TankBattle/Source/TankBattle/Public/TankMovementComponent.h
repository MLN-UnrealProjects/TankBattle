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
	//Performs a forward movement
	void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable, Category = "Input")
	//Performs a clocwise turn
	void IntendTurnClockwise(float Throw);
	UFUNCTION(Category = "Setup", BlueprintCallable)
	//Initializes Tracks to use for Force application. No logic is performed by this component if one or both tracks are nullptr
	void Initialize(UTankTrack* LeftTrack, UTankTrack* RightTrack);

private:
	//Called by pathfinding logic from aicontroller
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
