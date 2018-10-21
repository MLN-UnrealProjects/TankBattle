// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/RadialForceComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AProjectile::AProjectile() :
	ProjectileMovementComponent{ CreateDefaultSubobject<UProjectileMovementComponent>(FName{"Movement Component"}) },
	LaunchBlast{ CreateDefaultSubobject<UParticleSystemComponent>(FName{"PS Launch Blast"}) },
	CollisionMesh{ CreateDefaultSubobject<UStaticMeshComponent>(FName{"Collision Mesh"}) },
	ImpactBlast{ CreateDefaultSubobject<UParticleSystemComponent>(FName{"PS Impact Blast"}) },
	ExplosionForce{ CreateDefaultSubobject<URadialForceComponent>(FName{"Radial Force Component"}) }
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

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

	ExplosionForce->FireImpulse();

	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(this, ProjectileDamage, GetActorLocation(), ExplosionForce->Radius, UDamageType::StaticClass(), TArray<AActor*>());

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::DestroyProjectile, DestroyDelay, false, -1.0f);
}

void AProjectile::DestroyProjectile()
{
	Destroy();
}