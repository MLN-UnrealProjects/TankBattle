// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/PlayerController.h"
#include "CoreMinimal.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;
/**
 *
 */
UCLASS()
class TANKBATTLE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);
public:

	void AimTowardsCrosshair();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Setup")
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Setup")
	float CrossHairYLocation = 0.33333f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Setup")
	float LineTraceRange = 1000000.0f;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &OutHitLocation) const;

	virtual void SetPawn(APawn* InPawn) override;
	UFUNCTION()
	void OnDeath();
};
