// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"
#include "Runtime/CoreUObject/Public/UObject/NoExportTypes.h"
#include "Engine/World.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"
UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1.0f, 1.0f);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto Wheels{ GetWheels() };
	if (Wheels.Num() > 0)
	{
		auto ForceApplied{ CurrentThrottle * TrackMaxDrivingForce };
		auto ForcePerWheel = ForceApplied / Wheels.Num();
		for (ASprungWheel* Wheel : Wheels)
		{
			Wheel->AddDrivingForce(ForcePerWheel);
		}
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> Result;

	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Comp : Children)
	{
		USpawnPoint* SpawnPoint{ Cast<USpawnPoint>(Comp) };
		if (SpawnPoint)
		{
			auto Wheel{ Cast<ASprungWheel>(SpawnPoint->GetSpawnedActor()) };
			if (Wheel)
			{
				Result.Add(Wheel);
			}
		}
	}
	return Result;
}

//void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
//{
//	ApplySidewaysForce();
//}
//
//void UTankTrack::BeginPlay()
//{
//	Super::BeginPlay();
//	//OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
//}

//void UTankTrack::ApplySidewaysForce()
//{
//	auto Right{ GetRightVector() };
//
//	auto SlippageSpeed{ FVector::DotProduct(Right,GetComponentVelocity()) };
//
//	auto CorrectionAcceleration{ -(SlippageSpeed / GetWorld()->GetDeltaSeconds()) * Right };
//
//	auto Owner{ GetOwner() };
//	if (!ensure(Owner))
//		return;
//
//	auto RootComponent{ Cast<UStaticMeshComponent>(Owner->GetRootComponent()) };
//
//	auto CorrectionForce{ (RootComponent->GetMass() * CorrectionAcceleration) * 0.5f };
//
//	RootComponent->AddForce(CorrectionForce);
//}