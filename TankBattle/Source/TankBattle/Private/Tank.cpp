// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

//void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
//{
//	if (ensure(TankAimingComponent))
//	{
//		TankAimingComponent->SetBarrelReference(BarrelToSet);
//
//			Barrel = BarrelToSet;
//	}
//}
//
//void ATank::SetTurretReference(UTankTurret * TurretToSet)
//{
//	if (ensure(TankAimingComponent))
//		TankAimingComponent->SetTurretReference(TurretToSet);
//}
// Sets default values
ATank::ATank() //: TankAimingComponent{ CreateDefaultSubobject<UTankAimingComponent>(FName{"Aiming Component"}) }
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

// Called to bind functionality to input
//void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//}
float ATank::GetHealthPercentage() const
{
	if (CurrentHealth <= 0)
		return 0.0f;
	return (static_cast<float>(CurrentHealth) / static_cast<float>(StartingHealth));
}
float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	int32 DamageToApply{ FMath::Clamp<int32>(FPlatformMath::RoundToInt(DamageAmount), 0, CurrentHealth) };

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return DamageToApply;
}
