// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return static_cast<ATank*>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	int32 ViewportSizeX{ 0 }, ViewportSizeY{ 0 };
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	float CrossHairXLocation{ 0.5f }, CrossHairYLocation{ 0.33333 };
	FVector2D ScreenLocation{ ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation };
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s") , *(ScreenLocation.ToString()))
	return false;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* ControlledTank{ GetControlledTank() };
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank controlled: None"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank controlled: %s"), *(ControlledTank->GetName()))
	}
}
void ATankPlayerController::AimTowardsCrosshair()
{
	ATank* ControlledTank{ GetControlledTank() };
	if (!ControlledTank)
	{
		return;
	}
	FVector HitLocation{ 0.0f,0.0f,0.0f };

	if (GetSightRayHitLocation(HitLocation))
	{

	}
}