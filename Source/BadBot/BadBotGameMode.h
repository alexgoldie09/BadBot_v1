// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BadBotGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BADBOT_API ABadBotGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "MyPlayer")
	int PlayerScore = 0;

	// Public functions
	UFUNCTION(BlueprintCallable, Category = "MyPlayer")
	void IncrementScore();
};
