// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	//SpawnActor will call all initialization functions (ctor, begin play and same for BP). The SpawnDeferredActor will only call the c++ ctor (this must be followed by UGameplayStatics::FinishSpawningActor
	//auto SpawnedActor{ GetWorld()->SpawnActor<AActor>(ActorToSpawn) };
	AActor* SpawnedActor{ (GetWorld()->SpawnActorDeferred<AActor>(ActorToSpawn,FTransform::Identity,nullptr,nullptr,ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn)) };
	if (SpawnedActor)
	{
		SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
	UGameplayStatics::FinishSpawningActor(SpawnedActor, FTransform::Identity);
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

