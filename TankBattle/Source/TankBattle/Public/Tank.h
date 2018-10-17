// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;
class AProjectile;
class UTankMovementComponent;
UCLASS()
class TANKBATTLE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

protected:

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing", meta = (AllowPrivateAccess = "True"))
	float LaunchSpeed = 100000.0f; //TODO: find sensible speed

	UPROPERTY(EditDefaultsOnly, Category = "Setup", meta = (AllowPrivateAccess = "True"))
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr; //This is another way of saying UClass* ProjectileBlueprint, but instead of allowing any type of UClass it requests specifically a given type

	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing", meta = (AllowPrivateAccess = "True"))
	float ReloadTimeInSeconds = 1.0f;

	double LastFireTime = 0.0;
};
