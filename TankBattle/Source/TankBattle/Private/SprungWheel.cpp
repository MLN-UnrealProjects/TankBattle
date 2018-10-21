// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Engine/World.h"
// Sets default values
ASprungWheel::ASprungWheel() :
	MassAxelConstraint{ CreateDefaultSubobject<UPhysicsConstraintComponent>(FName{"Mass-Axel Constraint Component"}) },
	AxelWheelConstraint{ CreateDefaultSubobject<UPhysicsConstraintComponent>(FName{"Axel-Wheel Constraint Component"}) },
	//Mass{ CreateDefaultSubobject<UStaticMeshComponent>(FName{"Mass"}) },
	Wheel{ CreateDefaultSubobject<USphereComponent>(FName{"Wheel"}) },
	Axle{ CreateDefaultSubobject<USphereComponent>(FName{"Axel"}) }
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = ETickingGroup::TG_PostPhysics;

	//Constraint used as root because it does not simulate physics itself. If either mass or wheel were to be roots it is going to actually "pop out" of the hiearchy
	SetRootComponent(MassAxelConstraint);

	Axle->SetupAttachment(MassAxelConstraint);
	AxelWheelConstraint->SetupAttachment(Axle);
	Wheel->SetupAttachment(Axle);
	//Mass->SetupAttachment(MassWheelConstraint);

	//Mass->SetSimulatePhysics(true);
	Wheel->SetSimulatePhysics(true);
	Axle->SetSimulatePhysics(true);

	Axle->SetCollisionProfileName(FName{ "OverlapAll" });
	Wheel->SetCollisionProfileName(FName{ "BlockAllDynamic" });
	Axle->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);

	//MassWheelConstraint->ComponentName1 = FConstrainComponentPropName{ "Mass" };
	//MassWheelConstraint->ComponentName2 = FConstrainComponentPropName{ "Wheel" };

	MassAxelConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	MassAxelConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	MassAxelConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);

	MassAxelConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	MassAxelConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	MassAxelConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);

	MassAxelConstraint->SetLinearPositionDrive(false, false, true);
	MassAxelConstraint->SetLinearVelocityDrive(false, false, true);

	MassAxelConstraint->SetLinearDriveParams(5000.0f, 2000.0f, 0.0f);

	AxelWheelConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	AxelWheelConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	AxelWheelConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);

	AxelWheelConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	AxelWheelConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Free, 0.0f);
	AxelWheelConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);

	AxelWheelConstraint->SetLinearPositionDrive(false, false, false);
	AxelWheelConstraint->SetLinearVelocityDrive(false, false, false);

	//AxelWheelConstraint->SetLinearDriveParams(0.0f, 0.0f, 0.0f);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.TickGroup = ETickingGroup::TG_PostPhysics;

	AActor* Parent{ GetAttachParentActor() };
	if ((Parent))
	{
		UPrimitiveComponent* ParentRootForConstraint{ Cast<UPrimitiveComponent>(Parent->GetRootComponent()) };
		if ((ParentRootForConstraint))
		{
			MassAxelConstraint->SetConstrainedComponents(ParentRootForConstraint, NAME_None, Axle, NAME_None);
			AxelWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
		}
	}
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddUniqueDynamic(this, &ASprungWheel::OnHit);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ensure(GetWorld()->TickGroup == ETickingGroup::TG_PostPhysics))
	{
		CurrentForce = 0.0f;
	}
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	CurrentForce += ForceMagnitude;
}

void ASprungWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	Wheel->AddForce(Axle->GetForwardVector() * CurrentForce);
}

