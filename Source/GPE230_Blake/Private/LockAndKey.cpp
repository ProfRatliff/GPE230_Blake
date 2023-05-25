// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeCharacter.h"
#include "LockAndKey.h"

ALockAndKey::ALockAndKey()
{
	//Call CheckActorType when this trigger is overlapped
	OnActorBeginOverlap.AddDynamic(this, &ALockAndKey::CheckActorType);
}

void ALockAndKey::CheckActorType(class AActor* OverlappedActor, class AActor* OtherActor)
{
	//If the other actor is a maze character
	if (OtherActor->IsA(AMazeCharacter::StaticClass()))
		OpenTheDoor();
}

void ALockAndKey::OpenTheDoor()
{
	//Open the door (and remove the key) by destroying the parent object
	this->Destroy();
}

