// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MazeCharacter.h"
#include "VictoryTriggerVolume.generated.h"

/**
 * 
 */
UCLASS()
class GPE230_BLAKE_API AVictoryTriggerVolume : public ATriggerBox
{
	GENERATED_BODY()

protected:
	AVictoryTriggerVolume();

	UFUNCTION()
		void CheckActorType(class AActor* OverlappedActor, class AActor* OtherActor);
	
	UFUNCTION()
		void OpenVictoryScreen(class AMazeCharacter* PlayerChar);
};
