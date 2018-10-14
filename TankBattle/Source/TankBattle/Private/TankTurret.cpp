// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);

	auto NewRotation{ (RelativeSpeed *  (GetWorld()->DeltaTimeSeconds) * MaxDegreesPerSecond) + RelativeRotation.Yaw };

	SetRelativeRotation(FRotator{ 0.0f,NewRotation,0.0f });
}

