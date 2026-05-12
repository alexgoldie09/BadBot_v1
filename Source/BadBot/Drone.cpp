// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADrone::ADrone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ADrone::FindPlayerPawn, PawnSearchDelay, false);
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TargetPawn)
		return;

}

void ADrone::FindPlayerPawn()
{
	TargetPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

