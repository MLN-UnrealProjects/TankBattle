// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

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
void ATank::Fire()
{
	if (!ensure(ProjectileBlueprint && Barrel))
	{
		return;
	}

	double CurrentSeconds{ FPlatformTime::Seconds() };
	bool IsReloaded{ CurrentSeconds - LastFireTime > ReloadTimeInSeconds };
	if (!IsReloaded)
	{
		return;
	}

	LastFireTime = CurrentSeconds;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketTransform(FName{ "Projectile" }));
	Projectile->Launch(LaunchSpeed);
}
// Sets default values
ATank::ATank() //: TankAimingComponent{ CreateDefaultSubobject<UTankAimingComponent>(FName{"Aiming Component"}) }
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
void ATank::AimAt(FVector HitLocation)
{
	if (ensure(TankAimingComponent))
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}
// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); //Needed for BP begin play to execute
	//AActor* Owner{ GetOwner() };
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	//TankMovementComponent = Owner->FindComponentByClass<UTankMovementComponent>();
	//Barrel = Owner->FindComponentByClass<UTankBarrel>();
}

// Called to bind functionality to input
//void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//}