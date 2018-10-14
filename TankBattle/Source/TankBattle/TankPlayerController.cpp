// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return static_cast<ATank*>(GetPawn());
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
