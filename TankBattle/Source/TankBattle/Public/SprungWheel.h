// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"
class UPhysicsConstraintComponent;
class USphereComponent;
//class UStaticMeshComponent;
UCLASS()
class TANKBATTLE_API ASprungWheel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void AddDrivingForce(float ForceMagnitude);
private:
	UPROPERTY(VisibleAnywhere, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* MassAxelConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* AxelWheelConstraint = nullptr;
	//UPROPERTY(VisibleAnywhere, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	//UStaticMeshComponent* Mass = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	USphereComponent* Wheel = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	USphereComponent* Axle = nullptr;

	UFUNCTION()
	void OnHit(UPrimitiveComponent*  HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	float CurrentForce = 0.0f;
};
