// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

APickup::APickup()
{
	OnActorBeginOverlap.AddDynamic(this, &APickup::CheckActorType);
}

void APickup::CheckActorType(AActor* OverlappedActor, AActor* OtherActor)
{
	//Apply the pickup if the other actor is a maze character
	if (OtherActor->IsA(AMazeCharacter::StaticClass()))
		Apply(Cast<AMazeCharacter>(OtherActor));
}

void APickup::Apply(AMazeCharacter* PlayerChar)
{
	UE_LOG(LogTemp, Log, TEXT("Pickup %s was collected by %s."), this->GetDebugName, PlayerChar->GetDebugName);
}

void APickup::DestroySelf()
{
	this->Destroy();
}
