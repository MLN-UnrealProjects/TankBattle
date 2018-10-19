// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "Engine/EngineBaseTypes.h"
#include "Runtime/CoreUObject/Public/UObject/NoExportTypes.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
}
bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel))
		return false;
	auto BarrelForward{ Barrel->GetForwardVector() };
	return !(BarrelForward.Equals(AimDirection, 0.001f));
}
void UTankAimingComponent::Fire()
{
	if (AmmoLeft <= 0 || !ensure(ProjectileBlueprint && Barrel) || CurrentFireState == EFiringState::Reloading)
	{
		return;
	}
	AmmoLeft--;
	LastFireTime = FPlatformTime::Seconds();

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketTransform(FName{ "Projectile" }));
	Projectile->Launch(LaunchSpeed);
}
void UTankAimingComponent::AimAt(FVector Location)
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
EFiringState UTankAimingComponent::GetFiringState() const
{
	return CurrentFireState;
}
void UTankAimingComponent::MoveBarrelTowards(FVector DesiredDirection)
{
	if (!ensure(Barrel && Turret))
	{
		return;
	}

	AimDirection = DesiredDirection;

	auto BarrelRotator{ Barrel->GetForwardVector().Rotation() };
	auto AimAsRotator{ DesiredDirection.Rotation() };
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	float FinalRotation{ DeltaRotator.Yaw };
	if (FMath::Abs(DeltaRotator.Yaw) > 180.0f)
		FinalRotation *= -1.0f;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(FinalRotation);
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

int UTankAimingComponent::GetAmmoLeft() const
{
	return AmmoLeft;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (FPlatformTime::Seconds() - LastFireTime < ReloadTimeInSeconds)
		CurrentFireState = EFiringState::Reloading;
	else if (IsBarrelMoving())
		CurrentFireState = EFiringState::Aiming;
	else
		CurrentFireState = EFiringState::Locked;
}