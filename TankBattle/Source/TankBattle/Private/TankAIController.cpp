// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"
void ATankAIController::SetPawn(APawn * PossessedPawn)
{
	Super::SetPawn(PossessedPawn);
	if (PossessedPawn)
	{
		auto PossessedTank{ Cast<ATank>(PossessedPawn) };
		if (PossessedTank)
		{
			PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnDeath);
		}
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn{ GetWorld()->GetFirstPlayerController()->GetPawn() };
	if (!PlayerPawn)
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

void ATankAIController::OnDeath()
{
	APawn* MyPawn{ GetPawn() };
	if (MyPawn)
	{
		MyPawn->DetachFromControllerPendingDestroy();
	}
}
