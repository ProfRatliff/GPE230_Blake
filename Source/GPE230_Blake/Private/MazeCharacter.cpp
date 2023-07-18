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

	_controller = Cast<APlayerController>(GetController());

	_currentHealth = maxHealth;

	_gameOverScreenInstance = CreateWidget(GetWorld(), _gameOverScreenTemplate);
	_victoryScreenInstance = CreateWidget(GetWorld(), _victoryScreenTemplate);
}

/// <summary>
/// Apply incoming heal value to health and ensure it doesn't exceed max health.
/// </summary>
/// <param name="HealAmount"></param>
/// <returns></returns>
float AMazeCharacter::Heal(float HealAmount)
{
	if (!_isDead)
	{
		//Subtract incoming damage
		_currentHealth += HealAmount;
		_currentHealth = std::max(0.0f, std::min(_currentHealth, maxHealth));

		UE_LOG(LogTemp, Log, TEXT("Player healed %f points.  %f health remaining."), HealAmount, _currentHealth);

		if (_currentHealth <= 0)
			Die();

		return HealAmount;
	}
	else
		return 0;
}

/// <summary>
/// Apply incoming damage to health and check if the player was killed.
/// </summary>
/// <param name="DamageAmount">The amount of damage to be subtracted from current health.</param>
/// <param name="DamageEvent"></param>
/// <param name="EventInstigator"></param>
/// <param name="DamageCauser"></param>
/// <returns></returns>
float AMazeCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!_isDead)
	{
		//Subtract incoming damage
		_currentHealth -= DamageAmount;

		UE_LOG(LogTemp, Log, TEXT("Player took %f damage.  %f health remaining."), DamageAmount, _currentHealth);

		if (_currentHealth <= 0)
			Die();

		return DamageAmount;
	}
	else
		return 0;
}

void AMazeCharacter::Die()
{
	_isDead = true;
	_currentHealth = 0;

	GetMesh()->PlayAnimation(_deathAnim, false);

	OpenGameOverScreen();
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

void AMazeCharacter::OpenGameOverScreen()
{
	_gameOverScreenInstance->AddToViewport();

	ShowMouseCursor();

	FreezeCharacter();
}

void AMazeCharacter::OpenVictoryScreen()
{
	_victoryScreenInstance->AddToViewport();

	ShowMouseCursor();

	PauseGameplay(true);
}

float AMazeCharacter::GetCurrentHealth()
{
	return _currentHealth;
}

void AMazeCharacter::PauseGameplay(bool bIsPaused)
{
	_controller->SetPause(bIsPaused);
}

void AMazeCharacter::ShowMouseCursor()
{
	_controller->bShowMouseCursor = true;
}

void AMazeCharacter::FreezeCharacter()
{
	_moveSpeed = 0;
	_rotationSpeed = 0;
}

/// <summary>
/// Move forward or backward at a rate of "value" multiplied by moveSpeed.
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::MoveFB(float value)
{
	AddMovementInput(GetActorForwardVector(), value * _moveSpeed);
}

/// <summary>
/// Move left or right at a rate of "value" multiplied by moveSpeed.
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::MoveLR(float value)
{
	AddMovementInput(-GetActorRightVector(), value * _moveSpeed);
}

/// <summary>
/// Rotate at a rate of "value" multiplied by rotationSpeed.
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::Rotate(float value)
{
	AddControllerYawInput(value * _rotationSpeed);
}

/// <summary>
/// Briefly stun nearby enemies and activate a particle system to provide visual feedback for this action.
/// </summary>
void AMazeCharacter::ActivateStunParticleSystem()
{
	//Spawn a particle system and play it once
	if (_stunSystem)
	{
		USceneComponent* AttachComp = GetDefaultAttachComponent();

		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(_stunSystem, AttachComp, NAME_None,
			FVector(0), FRotator(0), EAttachLocation::Type::KeepRelativeOffset, true);

		NiagaraComp->Activate();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player attempted to use stun ability, but no template particle system was found."));
	}
}

