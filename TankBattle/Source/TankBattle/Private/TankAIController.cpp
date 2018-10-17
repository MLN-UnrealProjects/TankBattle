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

	APawn* Player{ GetWorld()->GetFirstPlayerController()->GetPawn() };
	if (!ensure(Player))
		return;

	APawn* MyTank{ GetPawn() };
	if (!ensure(MyTank))
		return;

	UTankAimingComponent* AimingComponent{ MyTank->FindComponentByClass<UTankAimingComponent>() };
	if (!ensure(AimingComponent))
		return;

	MoveToActor(Player, AcceptanceRadius);

	AimingComponent->AimAt(Player->GetActorLocation());
	AimingComponent->Fire();
}