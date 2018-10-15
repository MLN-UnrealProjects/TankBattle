// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack)
		return;

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}
void UTankMovementComponent::IntendTurnClockwise(float Throw)
{
	if (!LeftTrack || !RightTrack)
		return;

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::Initialize(UTankTrack * LeftTrack, UTankTrack * RightTrack)
{
	if (!LeftTrack || !RightTrack)
		return;

	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}
