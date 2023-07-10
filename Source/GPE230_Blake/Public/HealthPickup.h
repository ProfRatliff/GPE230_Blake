// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class GPE230_BLAKE_API AHealthPickup : public APickup
{
	GENERATED_BODY()
	
public:
	float healValue = 10;
	virtual void Apply(AMazeCharacter* PlayerChar) override;
};
