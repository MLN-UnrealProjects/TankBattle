// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
// Sets default values
AProjectile::AProjectile() : ProjectileMovementComponent{ CreateDefaultSubobject<UProjectileMovementComponent>(FName{"Movement Component"}) }, LaunchBlast{ CreateDefaultSubobject<UParticleSystemComponent>(FName{"PS Launch Blast"}) }, CollisionMesh{ CreateDefaultSubobject<UStaticMeshComponent>(FName{"Collision Mesh"}) }
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast->AttachTo(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::Launch(float Speed)
{
	if (!ensure(ProjectileMovementComponent))
	{
		return;
	}
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate();
}

