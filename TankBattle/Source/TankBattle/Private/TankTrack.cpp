// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"
UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}
void UTankTrack::SetThrottle(float Throttle)
{
	Throttle = FMath::Clamp(Throttle, -1.0f, 1.0f);


	auto ForceApplied{ GetForwardVector() * Throttle * TrackMaxDrivingForce };
	auto ForceLocation{ GetComponentLocation() };
	auto TankRoot{ Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()) };

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	auto Right{ GetRightVector() };

	auto SlippageSpeed{ FVector::DotProduct(Right,GetComponentVelocity()) };

	auto CorrectionAcceleration{ -(SlippageSpeed / DeltaTime) * Right };

	auto Owner{ GetOwner() };
	if (!ensure(Owner))
		return;

	auto RootComponent{ Cast<UStaticMeshComponent>(Owner->GetRootComponent()) };

	auto CorrectionForce{ (RootComponent->GetMass() * CorrectionAcceleration) * 0.5f };

	UE_LOG(LogTemp, Warning, TEXT("%s"), *CorrectionForce.ToString());

	RootComponent->AddForce(CorrectionForce);
}
