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


// Called to bind functionality to input
//void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//}