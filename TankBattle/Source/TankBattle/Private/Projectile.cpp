// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/EngineTypes.h"
#include "Components/PrimitiveComponent.h"
AProjectile::AProjectile() : ProjectileMovementComponent{ CreateDefaultSubobject<UProjectileMovementComponent>(FName{"Movement Component"}) }, LaunchBlast{ CreateDefaultSubobject<UParticleSystemComponent>(FName{"PS Launch Blast"}) }, CollisionMesh{ CreateDefaultSubobject<UStaticMeshComponent>(FName{"Collision Mesh"}) }, ImpactBlast{ CreateDefaultSubobject<UParticleSystemComponent>(FName{"PS Impact Blast"}) }
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	PrimaryActorTick.bCanEverTick = false;
	ProjectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
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

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
}

