// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	OutHitLocation = FVector(0.0f);

	int32 ViewportSizeX{ 0 }, ViewportSizeY{ 0 };
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	float CrossHairXLocation{ 0.5f }, CrossHairYLocation{ 0.33333 };
	FVector2D ScreenLocation{ ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation };
	FVector LookDirection{ 0.0f,0.0f,0.0f };

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return false;
}
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &OutHitLocation) const
{
	FVector StartLocation{ PlayerCameraManager->GetCameraLocation() };
	FVector EndLocation{ StartLocation + LookDirection * LineTraceRange };

	FHitResult hit;
	bool result{ GetWorld()->LineTraceSingleByChannel(hit, StartLocation, StartLocation + (LookDirection * LineTraceRange), ECollisionChannel::ECC_Camera) };
	OutHitLocation = hit.Location;

	return result;
}
void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank{ Cast<ATank>(InPawn) };
		if (PossessedTank)
		{
			PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnDeath);
		}
	}
}
void ATankPlayerController::OnDeath()
{
	StartSpectatingOnly();
}
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation{ 0.0f,0.0f,0.0f };
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	APawn* MyPawn{ GetPawn() };
	if (!MyPawn)
		return;

	UTankAimingComponent* aimer{ MyPawn->FindComponentByClass<UTankAimingComponent>() };
	if (!aimer)
		return;

	FoundAimingComponent(aimer);
}
void ATankPlayerController::AimTowardsCrosshair()
{
	APawn* MyPawn{ GetPawn() };
	if (!MyPawn)
		return;

	UTankAimingComponent* aimer{ MyPawn->FindComponentByClass<UTankAimingComponent>() };
	if (!aimer)
		return;

	FVector HitLocation{ 0.0f,0.0f,0.0f };

	if (GetSightRayHitLocation(HitLocation))
	{
		aimer->AimAt(HitLocation);
	}
}