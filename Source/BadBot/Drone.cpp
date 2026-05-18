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
		SocketRifleL = DroneMesh->GetSocketTransform(FName("Rifle_L"));
		SocketRifleR = DroneMesh->GetSocketTransform(FName("Rifle_R"));
	}
}

void ADrone::FindPlayerPawn()
{
	TargetPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!TargetPawn) return;

	OnTargetFound();
}

void ADrone::SpawnBlasterBolt(FTransform SpawnTransform)
{
	if (!TargetPawn) return;
	if (!BlasterBoltClass) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector SpawnLocation = SpawnTransform.GetLocation();
	FRotator SpawnRotation = (TargetPawn->GetActorLocation() - SpawnLocation).Rotation();

	GetWorld()->SpawnActor<AActor>(BlasterBoltClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (MuzzleFlashEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			MuzzleFlashEffect,
			SpawnLocation,
			SpawnTransform.GetRotation().Rotator(),
			FVector(1.0f),
			true,    // auto destroy
			true,    // auto activate
			ENCPoolMethod::None
		);
	}

	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			FireSound,
			SpawnLocation
		);
	}
}

