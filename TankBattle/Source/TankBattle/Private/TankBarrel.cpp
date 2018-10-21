// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);

	auto ElevationChange{ GetWorld()->DeltaTimeSeconds * RelativeSpeed * MaxDegreesPerSecond };
	auto RawNewElevation{ RelativeRotation.Pitch + ElevationChange};

	auto NewElevation{ FMath::Clamp(RawNewElevation,MinElevationDegrees,MaxElevationDegrees) };

	SetRelativeRotation(FRotator{ NewElevation,0.0f,0.0f });
}

