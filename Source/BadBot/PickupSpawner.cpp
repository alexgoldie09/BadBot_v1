// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupSpawner.h"

// Sets default values
APickupSpawner::APickupSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickupSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// DrawDebugSphere(
	// 	GetWorld(),
	// 	GetActorLocation(),
	// 	SpawnRadius,
	// 	12,
	// 	FColor::Green,
	// 	false,
	// 	0.0f,
	// 	0,
	// 	1.0f
	// );

}

FVector APickupSpawner::GetRandomPointInSphere()
{
	FVector RandomDirection = FMath::VRand();
	float RandomDistance = FMath::FRandRange(0.0f, SpawnRadius);
	return GetActorLocation() + RandomDirection * RandomDistance;
}

