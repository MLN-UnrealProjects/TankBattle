// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"
struct FActorComponentTickFunction;
/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

	UTankTrack();

public:
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetThrottle(float Throttle);


	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Movement")
	float TrackMaxDrivingForce = 40000000.0f;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	virtual void BeginPlay() override;
	void ApplySidewaysForce();
	void DriveTrack();

	float CurrentThrottle = 0.0f;
};
