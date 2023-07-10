// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MazeCharacter.h"
#include "Pickup.generated.h"

/**
 * 
 */
UCLASS()
class GPE230_BLAKE_API APickup : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	APickup();

	UFUNCTION()
		void CheckActorType(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
		virtual void Apply(AMazeCharacter* PlayerChar);

	UFUNCTION()
		void DestroySelf();
};
