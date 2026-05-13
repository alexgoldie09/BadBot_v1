// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterBolt.h"

// Sets default values
ABlasterBolt::ABlasterBolt()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABlasterBolt::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlasterBolt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

