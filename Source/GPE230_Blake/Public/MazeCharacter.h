// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Engine/SkeletalMesh.h"
#include "Camera/CameraComponent.h"

#include "MazeCharacter.generated.h"

UCLASS()
class GPE230_BLAKE_API AMazeCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float moveSpeed;
	UPROPERTY(EditAnywhere)
		float rotationSpeed;
	UPROPERTY(EditAnywhere)
	UAnimSequence* deathAnim;

protected:
	/// <summary>
	/// The current health of this character.
	/// </summary>
	float _currentHealth;

public:
	/// <summary>
	/// The maximum and starting health for this character.
	/// </summary>
	UPROPERTY(EditAnywhere)
	float maxHealth;

	/// <summary>
	/// Is this player dead and ready to restart the level?
	/// </summary>
	bool isDead = false;

public:
	// Sets default values for this character's properties
	AMazeCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
		AActor* DamageCauser) override;
	virtual void Die();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveFB(float value);
	void MoveLR(float value);
	void Rotate(float value);
};
