// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"
#include "Runtime/CoreUObject/Public/UObject/NoExportTypes.h"
#include "Engine/World.h"
UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.0f, 1.0f);
	//AddForce(ForceApplied);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *ForceApplied.ToString());
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied{ GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce };
	auto ForceLocation{ GetComponentLocation() };
	auto TankRoot{ Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()) };

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0.0f;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewaysForce()
{
	auto Right{ GetRightVector() };

	auto SlippageSpeed{ FVector::DotProduct(Right,GetComponentVelocity()) };

	auto CorrectionAcceleration{ -(SlippageSpeed / GetWorld()->GetDeltaSeconds()) * Right };

	auto Owner{ GetOwner() };
	if (!ensure(Owner))
		return;

	auto RootComponent{ Cast<UStaticMeshComponent>(Owner->GetRootComponent()) };

	auto CorrectionForce{ (RootComponent->GetMass() * CorrectionAcceleration) * 0.5f };

	RootComponent->AddForce(CorrectionForce);
}