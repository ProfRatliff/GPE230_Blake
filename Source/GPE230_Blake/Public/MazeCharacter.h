// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/EngineBaseTypes.h"

#include "Engine/SkeletalMesh.h"
#include "Camera/CameraComponent.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "Blueprint/UserWidget.h"

#include "MazeCharacter.generated.h"

UCLASS()
class GPE230_BLAKE_API AMazeCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float _moveSpeed;
	UPROPERTY(EditAnywhere)
		float _rotationSpeed;
	UPROPERTY(EditAnywhere)
		UAnimSequence* _deathAnim;
	UPROPERTY(EditAnywhere)
		UNiagaraSystem* _stunSystem;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> _gameOverScreenTemplate;
	UUserWidget* _gameOverScreenInstance;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> _victoryScreenTemplate;
	UUserWidget* _victoryScreenInstance;
	bool _isDead = false;


protected:
	/// <summary>
	/// The current health of this character.
	/// </summary>
	float _currentHealth;

	/// <summary>
	/// The controller that manages this character.
	/// </summary>
	APlayerController* _controller;

public:
	/// <summary>
	/// The maximum and starting health for this character.
	/// </summary>
	UPROPERTY(EditAnywhere)
		float maxHealth;

public:
	// Sets default values for this character's properties
	AMazeCharacter();
	virtual float Heal(float HealAmount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
		AActor* DamageCauser) override;
	virtual void Die();
	virtual void TriggerGameOverScreen();
	virtual void PauseGameplay(bool bIsPaused);
	virtual void ShowMouseCursor();
	virtual void FreezeCharacter();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void TriggerVictoryScreen();

private:
	void MoveFB(float value);
	void MoveLR(float value);
	void Rotate(float value);
	UFUNCTION(BlueprintCallable)
	void ActivateStunParticleSystem();
};
