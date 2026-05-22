#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "BotPawn.generated.h"

UCLASS()
class BADBOT_API ABotPawn : public APawn
{
	GENERATED_BODY()

public:
	ABotPawn();
	
	// Inputs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* FireInputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	int32 MappingPriority = 0;
	
	UPROPERTY(BlueprintReadOnly, Category = "Input")
	APlayerController* PlayerController = nullptr;
	
	// Mesh and Sockets
	UPROPERTY(BlueprintReadOnly, Category = "Player Settings|Combat")
	UStaticMeshComponent* DroneMesh = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Player Settings|Combat")
	FTransform SocketRifleL;

	UPROPERTY(BlueprintReadOnly, Category = "Player Settings|Combat")
	FTransform SocketRifleR;
	
	// Combat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings|Combat")
	TSubclassOf<AActor> BlasterBoltClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings|Combat")
	float FireRate = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings|Combat")
	bool bAlternatefire = true;

	// Audio & Effects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings|Combat")
	UNiagaraSystem* MuzzleFlashEffect = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings|Combat")
	USoundBase* FireSound = nullptr;
	
	// Public functions
	UFUNCTION(BlueprintCallable, Category = "Player Settings|Combat")
	void SpawnBlasterBolt(FTransform SpawnTransform);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};