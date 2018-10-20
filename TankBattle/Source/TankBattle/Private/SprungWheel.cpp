// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
// Sets default values
ASprungWheel::ASprungWheel() :
	MassWheelConstraint{ CreateDefaultSubobject<UPhysicsConstraintComponent>(FName{"Physics Constraint Component"}) },
	Mass{ CreateDefaultSubobject<UStaticMeshComponent>(FName{"Mass"}) },
	Wheel{ CreateDefaultSubobject<UStaticMeshComponent>(FName{"Wheel"}) }
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Constraint used as root because it does not simulate physics itself. If either mass or wheel were to be roots it is going to actually "pop out" of the hiearchy
	SetRootComponent(MassWheelConstraint);

	Wheel->SetupAttachment(MassWheelConstraint);
	Mass->SetupAttachment(MassWheelConstraint);

	Mass->SetSimulatePhysics(true);
	Wheel->SetSimulatePhysics(true);

	MassWheelConstraint->ComponentName1 = FConstrainComponentPropName{ "Mass" };
	MassWheelConstraint->ComponentName2 = FConstrainComponentPropName{ "Wheel" };

	MassWheelConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	MassWheelConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	MassWheelConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);

	MassWheelConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	MassWheelConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	MassWheelConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);

	MassWheelConstraint->SetLinearPositionDrive(false, false, true);
	MassWheelConstraint->SetLinearVelocityDrive(false, false, true);

	MassWheelConstraint->SetLinearDriveParams(5000.0f, 2000.0f, 0.0f);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

