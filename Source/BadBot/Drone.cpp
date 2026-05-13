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
	
	DroneMesh = FindComponentByClass<UStaticMeshComponent>();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ADrone::FindPlayerPawn, PawnSearchDelay, false);
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TargetPawn) return;

	if (DroneMesh)
	{
		SocketRifleL = DroneMesh->GetSocketLocation(FName("Rifle_L"));
		SocketRifleR = DroneMesh->GetSocketLocation(FName("Rifle_R"));
	}

	FireTimer += DeltaTime;
	if (FireTimer >= FireRate)
	{
		FireTimer = 0.0f;
		OnReadyToFire();
	}
}

void ADrone::FindPlayerPawn()
{
	TargetPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void ADrone::SpawnBlasterBolt(FVector SpawnLocation)
{
	if (!TargetPawn) return;
	if (!BlasterBoltClass) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FRotator SpawnRotation = (TargetPawn->GetActorLocation() - SpawnLocation).Rotation();

	GetWorld()->SpawnActor<AActor>(BlasterBoltClass, SpawnLocation, SpawnRotation, SpawnParams);
}

