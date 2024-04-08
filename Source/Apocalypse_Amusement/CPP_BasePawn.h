// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Components/AudioComponent.h"

#include "CPP_BasePawn.generated.h"

UCLASS()
class APOCALYPSE_AMUSEMENT_API ACPP_BasePawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPP_BasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Accessor 
	// Get the controlled pawn name
	FName GetPawnName() const;

	// Get the Current Health value
	float GetCurrentHealth() const;

	// Get the Max Health value
	float GetMaxHealth() const;

	// Get the spawn location
	FVector GetSpawnLocation() const;

	// Get the bIsAlive
	bool IsAlive() const;

	// Mutator
	// Set the current health value
	void SetCurrentHealth(float NewCurrentHealth);
	void SetStartingHealth();

	// Set the max health value  
	void SetMaxHealth(float NewMaxHealth);

	// Set the health when take damage
	void TakeDamageWhenHit(float DamageValue);

	// Functions
	// Play Sound 
	void PlaySound();

	// Pause Sound
	void PauseSound();

	// Stop Sound
	void StopSound();

	// Handle Hit
	virtual void HandleHit(int32 WeaponIdentifier, int32 damage);

protected:

	// Name
	FName PawnName;

	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = true))
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = true))
	float MaxHealth;

	// Location
	FVector PawnLocation;

	// Spawn Location
	UPROPERTY(EditAnywhere, Category = "Spawn Location", meta = (AllowPrivateAccess = true))
	FVector SpawnLocation;

	// Damage
	float Damage;

	// Bool for checking if is alive
	bool bIsAlive = true;

	// MovementSpeed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Speed", meta = (AllowPrivateAccess = true))
	float MovementSpeed = 600.f;

	// Sound Base
	UPROPERTY(EditAnywhere, Category = "Sound", meta = (AllowPrivateAccess = true))
	USoundBase* SoundBase;

	UAudioComponent* AudioComponent;
};
