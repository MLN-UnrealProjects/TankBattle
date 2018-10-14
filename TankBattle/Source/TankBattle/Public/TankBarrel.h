// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) , hidecategories = ("Collision"))
class TANKBATTLE_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 is max downwards speed and +1 is max upwards speed
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float MaxDegreesPerSecond = 20.0f;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float MaxElevationDegrees = 40.0f;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float MinElevationDegrees = 0.0f;
};
