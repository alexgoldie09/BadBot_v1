// Fill out your copyright notice in the Description page of Project Settings.


#include "BotPawn.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABotPawn::ABotPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABotPawn::BeginPlay()
{
	Super::BeginPlay();
	
	DroneMesh = FindComponentByClass<UStaticMeshComponent>();
	
	PlayerController = Cast<APlayerController>(GetController());

	if (InputMappingContext)
	{
		if (PlayerController)
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(InputMappingContext, MappingPriority);
			}
		}

		// Get mappings from the context and find the pulse trigger for the FireInput
		for (const FEnhancedActionKeyMapping& Mapping : InputMappingContext->GetMappings())
		{
			if (Mapping.Action == FireInputAction)
			{
				for (UInputTrigger* Trigger : Mapping.Action->Triggers)
				{
					if (UInputTriggerPulse* PulseTrigger = Cast<UInputTriggerPulse>(Trigger))
					{
						PulseTrigger->Interval = FireRate;
						break;
					}
				}
				break;
			}
		}
	}
}

// Called every frame
void ABotPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DroneMesh)
	{
		SocketRifleL = DroneMesh->GetSocketTransform(FName("Rifle_L"));
		SocketRifleR = DroneMesh->GetSocketTransform(FName("Rifle_R"));
	}
}

// Called to bind functionality to input
void ABotPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABotPawn::SpawnBlasterBolt(FTransform SpawnTransform)
{
	if (!BlasterBoltClass) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLocation = SpawnTransform.GetLocation();
	FRotator SpawnRotation = SpawnTransform.GetRotation().Rotator();

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

