// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))
		return;

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}
void UTankMovementComponent::IntendTurnClockwise(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))
		return;

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::Initialize(UTankTrack * LeftTrack, UTankTrack * RightTrack)
{
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward{ GetOwner()->GetActorForwardVector().GetSafeNormal() };
	auto ForwardIntention{ MoveVelocity.GetSafeNormal() };
	IntendMoveForward(FVector::DotProduct(TankForward, ForwardIntention));
	IntendTurnClockwise(FVector::CrossProduct(TankForward, ForwardIntention).Z);
}
