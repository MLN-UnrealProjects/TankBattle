// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetThrottle(float Throttle);
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") , Category = "Movement")
	float TrackMaxDrivingForce = 400000.0f; 
};
