// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryTriggerVolume.h"

AVictoryTriggerVolume::AVictoryTriggerVolume()
{
	OnActorBeginOverlap.AddDynamic(this, &AVictoryTriggerVolume::CheckActorType);
}

void AVictoryTriggerVolume::CheckActorType(AActor* OverlappedActor, AActor* OtherActor)
{
	// Open the victory screen if the character that entered this trigger is the player
	if (OtherActor->IsA(AMazeCharacter::StaticClass()))
		OpenVictoryScreen(Cast<AMazeCharacter>(OtherActor));
}

void AVictoryTriggerVolume::OpenVictoryScreen(AMazeCharacter* PlayerChar)
{
	PlayerChar->OpenVictoryScreen();
}
