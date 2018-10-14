// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"



ATank* ATankAIController::GetControlledTank() const
{
	return static_cast<ATank*>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	ATank* ControlledTank{ GetControlledTank() };
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank controlled: None"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank controlled: %s"), *(ControlledTank->GetName()))
	}
}