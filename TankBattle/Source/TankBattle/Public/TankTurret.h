// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Rotate(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float MaxDegreesPerSecond = 25.0f;
};
