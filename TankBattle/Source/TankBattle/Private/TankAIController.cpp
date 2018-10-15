// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankPlayerController.h"
#include "GameFramework/Actor.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* Player{ (Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController()))->GetControlledTank() };
	if (!Player)
		return;

	ATank* MyTank{ Cast<ATank>(GetPawn()) };
	if (!MyTank)
		return;

	MyTank->AimAt(Player->GetActorLocation());
	MyTank->Fire();
}