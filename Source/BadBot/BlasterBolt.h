// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "BlasterBolt.generated.h"

UCLASS()
class BADBOT_API ABlasterBolt : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlasterBolt();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bolt|Effects")
	UNiagaraSystem* ImpactEffect = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
				UPrimitiveComponent* OtherComp, FVector NormalImpulse, 
				const FHitResult& Hit);

};
