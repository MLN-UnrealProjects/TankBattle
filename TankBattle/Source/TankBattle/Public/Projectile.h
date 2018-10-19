// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"
class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;
UCLASS()
class TANKBATTLE_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Launch(float Speed);

private:
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere , Category = "Setup", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* LaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* ImpactBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	URadialForceComponent* ExplosionForce = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Hit", meta = (AllowPrivateAccess = "true"))
	float DestroyDelay = 3.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Hit", meta = (AllowPrivateAccess = "true"))
	float ProjectileDamage = 20.0f;

	void DestroyProjectile();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
