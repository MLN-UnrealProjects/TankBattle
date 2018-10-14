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
	ATank* ControlledTank{ GetControlledTank() };
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank controlled: None"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank controlled: %s"), *(ControlledTank->GetName()))
	}
	ATank* PlayerTank{ GetPlayerTank() };
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI did not found player tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Ai found player tank : %s"), *(PlayerTank->GetName()))
	}
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
	ATankPlayerController* player{ static_cast<ATankPlayerController*>(GetWorld()->GetFirstPlayerController()) };

	if (!player)
		return nullptr;

	return player->GetControlledTank();
}
