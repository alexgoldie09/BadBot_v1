// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupSpawner.generated.h"

UCLASS()
class BADBOT_API APickupSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupSpawner();

	// Spawn Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Spawner|Settings")
	TSubclassOf<AActor> PickupClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Spawner|Settings")
	float SpawnRadius = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Spawner|Settings")
	float SpawnRate = 2.0f;

	// Public functions
	UFUNCTION(BlueprintPure, Category = "Pickup Spawner")
	FVector GetRandomPointInSphere();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
