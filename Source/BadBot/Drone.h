// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Drone.generated.h"

UCLASS()
class BADBOT_API ADrone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADrone();
	
	// Combat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Combat")
	TSubclassOf<AActor> BlasterBoltClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Combat")
	float FireRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Combat")
	float Damage = 10.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Drone|Combat")
	bool bFireLeft = true;

	// Mesh and Sockets
	UPROPERTY(BlueprintReadOnly, Category = "Drone|Combat")
	UStaticMeshComponent* DroneMesh = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Drone|Combat")
	FVector SocketRifleL;

	UPROPERTY(BlueprintReadOnly, Category = "Drone|Combat")
	FVector SocketRifleR;

	// Movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Movement")
	float MoveSpeed = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Movement")
	float RotateSpeed = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Movement")
	float PawnSearchDelay = 0.5f;

	// Target
	UPROPERTY(BlueprintReadWrite, Category = "Drone")
	APawn* TargetPawn = nullptr;

	// Public functions
	UFUNCTION(BlueprintCallable, Category = "Drone|Combat")
	void SpawnBlasterBolt(FVector SpawnLocation);

	UFUNCTION(BlueprintImplementableEvent, Category = "Drone|Combat")
	void OnReadyToFire();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	float FireTimer = 0.0f;
	void FindPlayerPawn();
};
