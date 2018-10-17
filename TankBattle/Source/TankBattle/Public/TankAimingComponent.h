// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:

	UPROPERTY(BlueprintReadOnly , Category = "State")
	EFiringState CurrentFireState = EFiringState::Locked;
public:
	void AimAt(FVector WorldHitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup", meta = (AllowPrivateAccess = "True"))
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr; //This is another way of saying UClass* ProjectileBlueprint, but instead of allowing any type of UClass it requests specifically a given type
	UPROPERTY(EditDefaultsOnly, Category = "Firing", meta = (AllowPrivateAccess = "True"))
	float LaunchSpeed = 4000.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Firing", meta = (AllowPrivateAccess = "True"))
	double ReloadTimeInSeconds = 2.0;

	double LastFireTime = -10.0;

	void MoveBarrelTowards(FVector DesiredDirection);
};
