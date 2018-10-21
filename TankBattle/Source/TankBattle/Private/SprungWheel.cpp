// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
// Sets default values
ASprungWheel::ASprungWheel() :
	MassAxelConstraint{ CreateDefaultSubobject<UPhysicsConstraintComponent>(FName{"Mass-Axel Constraint Component"}) },
	AxelWheelConstraint{ CreateDefaultSubobject<UPhysicsConstraintComponent>(FName{"Axel-Wheel Constraint Component"}) },
	//Mass{ CreateDefaultSubobject<UStaticMeshComponent>(FName{"Mass"}) },
	Wheel{ CreateDefaultSubobject<USphereComponent>(FName{"Wheel"}) },
	Axel{ CreateDefaultSubobject<USphereComponent>(FName{"Axel"}) }
{
	PrimaryActorTick.bCanEverTick = true;

	//Constraint used as root because it does not simulate physics itself. If either mass or wheel were to be roots it is going to actually "pop out" of the hiearchy
	SetRootComponent(MassAxelConstraint);

	Axel->SetupAttachment(MassAxelConstraint);
	AxelWheelConstraint->SetupAttachment(Axel);
	Wheel->SetupAttachment(Axel);
	//Mass->SetupAttachment(MassWheelConstraint);

	//Mass->SetSimulatePhysics(true);
	Wheel->SetSimulatePhysics(true);
	Axel->SetSimulatePhysics(true);

	Axel->SetCollisionProfileName(FName{ "OverlapAll" });
	Wheel->SetCollisionProfileName(FName{ "BlockAllDynamic" });
	Axel->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);

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

	AActor* Parent{ GetAttachParentActor() };
	if ((Parent))
	{
		UPrimitiveComponent* ParentRootForConstraint{ Cast<UPrimitiveComponent>(Parent->GetRootComponent()) };
		if ((ParentRootForConstraint))
		{
			MassAxelConstraint->SetConstrainedComponents(ParentRootForConstraint, NAME_None, Axel, NAME_None);
			AxelWheelConstraint->SetConstrainedComponents(Axel, NAME_None, Wheel, NAME_None);
		}
	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

