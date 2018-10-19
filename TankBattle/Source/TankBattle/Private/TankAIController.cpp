// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn{ GetWorld()->GetFirstPlayerController()->GetPawn() };
	if (!ensure(PlayerPawn))
		return;

	APawn* MyPawn{ GetPawn() };
	if (!MyPawn)
		return;

	UTankAimingComponent* AimingComponent{ MyPawn->FindComponentByClass<UTankAimingComponent>() };
	if (!ensure(AimingComponent))
		return;

	MoveToActor(PlayerPawn, AcceptanceRadius);

	AimingComponent->AimAt(PlayerPawn->GetActorLocation());
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
		AimingComponent->Fire();
}