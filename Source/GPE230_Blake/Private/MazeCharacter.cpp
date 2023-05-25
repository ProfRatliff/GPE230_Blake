// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCharacter.h"

// Sets default values
AMazeCharacter::AMazeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMazeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMazeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMazeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveFB"), this, &AMazeCharacter::MoveFB);
	PlayerInputComponent->BindAxis(TEXT("MoveLR"), this, &AMazeCharacter::MoveLR);
	PlayerInputComponent->BindAxis(TEXT("Rotate"), this, &AMazeCharacter::Rotate);
}

/// <summary>
/// Move forward or backward at a rate of "value" multiplied by moveSpeed.
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::MoveFB(float value)
{
	AddMovementInput(GetActorForwardVector(), value * moveSpeed);
}

/// <summary>
/// Move left or right at a rate of "value" multiplied by moveSpeed.
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::MoveLR(float value)
{
	AddMovementInput(-GetActorRightVector(), value * moveSpeed);
}

/// <summary>
/// Rotate at a rate of "value" multiplied by rotationSpeed.
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::Rotate(float value)
{
	AddControllerYawInput(value * rotationSpeed);
}

