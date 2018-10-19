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
struct FActorComponentTickFunction;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
	// Sets default values for this component's properties
	UTankAimingComponent();
	EFiringState GetFiringState() const;
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int AmmoLeft = 10;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState CurrentFireState = EFiringState::Reloading;
public:
	void AimAt(FVector WorldHitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetAmmoLeft() const;

private:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup", meta = (AllowPrivateAccess = "True"))
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr; //This is another way of saying UClass* ProjectileBlueprint, but instead of allowing any type of UClass it requests specifically a given type
	UPROPERTY(EditDefaultsOnly, Category = "Firing", meta = (AllowPrivateAccess = "True"))
	float LaunchSpeed = 8000.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Firing", meta = (AllowPrivateAccess = "True"))
	double ReloadTimeInSeconds = 2.0;

	double LastFireTime = 0.0;

	FVector AimDirection = FVector(0.0f);

	virtual void BeginPlay() override;

	bool IsBarrelMoving() const;

	void MoveBarrelTowards(FVector DesiredDirection);
};
