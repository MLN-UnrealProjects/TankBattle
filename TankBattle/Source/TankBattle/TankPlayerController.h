// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 *
 */
UCLASS()
class TANKBATTLE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void AimTowardsCrosshair();
	ATank* GetControlledTank() const;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float CrossHairXLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float CrossHairYLocation;

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
};
