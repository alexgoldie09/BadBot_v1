// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/KismetSystemLibrary.h"
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

	if (UStaticMeshComponent* BoltMesh = FindComponentByClass<UStaticMeshComponent>())
	{
		// BoltMesh->SetNotifyRigidBodyCollision(true);
		BoltMesh->OnComponentHit.AddDynamic(this, &ABlasterBolt::OnHit);
	}
}

// Called every frame
void ABlasterBolt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlasterBolt::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                          UPrimitiveComponent* OtherComp, FVector NormalImpulse,
                          const FHitResult& Hit)
{
    if (!OtherActor) return;
    if (OtherActor == GetOwner()) return;

    if (ImpactEffect)
    {
        FRotator ImpactRotation = Hit.ImpactNormal.Rotation();

        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            ImpactEffect,
            Hit.ImpactPoint,
            ImpactRotation,
            FVector(1.0f),
            true,
            true,
            ENCPoolMethod::None
        );
    }

    if (APawn* HitPawn = Cast<APawn>(OtherActor))
    {
        UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
    }

    Destroy();
}

