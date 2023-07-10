// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"

void AHealthPickup::Apply(AMazeCharacter* PlayerChar)
{
	PlayerChar->Heal(healValue);

	DestroySelf();
}
