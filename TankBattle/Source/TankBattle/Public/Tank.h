// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);

class UTankMovementComponent;
UCLASS()
class TANKBATTLE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	//Returns current health as percentage of starting health from 0 to 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage() const;

	FOnDeathDelegate OnDeath;
private:
	virtual void BeginPlay() override;
	ATank();
	UPROPERTY(EditDefaultsOnly, Category = "Setup" , meta = (AllowPrivateAccess = "true"))
	int32 StartingHealth = 200;
	int32 CurrentHealth = StartingHealth;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
};
