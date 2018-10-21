// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLE_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnPoint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	AActor* GetSpawnedActor() const;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AActor> ActorToSpawn = nullptr;
	UPROPERTY() //This allows the garbage collector to track this property
	AActor* SpawnedActor = nullptr;
};
