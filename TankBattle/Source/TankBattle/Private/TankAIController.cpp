// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankPlayerController.h"
#include "GameFramework/Actor.h"


ATank* ATankAIController::GetControlledTank() const
{
	return static_cast<ATank*>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ATank* Player{ GetPlayerTank() };
	if (!Player)
		return;

	ATank* MyTank{ GetControlledTank() };
	if (!MyTank)
		return;

	MyTank->AimAt(Player->GetActorLocation());
}

ATank * ATankAIController::GetPlayerTank() const
{
	APlayerController* Player{ GetWorld()->GetFirstPlayerController() };

	if (!Player)
		return nullptr;

	ATankPlayerController* CastedController{ dynamic_cast<ATankPlayerController*>(Player) };
	if (!CastedController)
		return nullptr;

	return CastedController->GetControlledTank();
}