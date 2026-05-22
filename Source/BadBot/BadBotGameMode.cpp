// Fill out your copyright notice in the Description page of Project Settings.


#include "BadBotGameMode.h"

void ABadBotGameMode::IncrementScore()
{
	PlayerScore++;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, 
		FString::Printf(TEXT("Score: %d"), PlayerScore));
}
