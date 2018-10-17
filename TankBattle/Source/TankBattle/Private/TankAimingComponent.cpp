// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector Location, float LaunchSpeed)
{
	if (!ensure(Barrel))
	{
		return;
	}
	FVector OutLaunchVelocity(0.0f);
	FVector StartLocation = Barrel->GetSocketLocation(FName{ "Projectile" });

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, Location, LaunchSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		MoveBarrelTowards(OutLaunchVelocity.GetSafeNormal());
	}
}
void UTankAimingComponent::MoveBarrelTowards(FVector DesiredDirection)
{
	if (!ensure(Barrel && Turret))
	{
		return;
	}

	auto BarrelRotator{ Barrel->GetForwardVector().Rotation() };
	auto AimAsRotator{ DesiredDirection.Rotation() };
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}
//void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
//{
//		Barrel = BarrelToSet;
//}
//
//void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
//{
//		Turret = TurretToSet;
//}

void UTankAimingComponent::Initialize(UTankTurret * TurretToSet, UTankBarrel* BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}