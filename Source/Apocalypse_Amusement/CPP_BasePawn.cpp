// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BasePawn.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACPP_BasePawn::ACPP_BasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create Audio Component for manipulating the audio  
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->SetAutoActivate(false); // dont activate at the begining

}

// Called when the game starts or when spawned
void ACPP_BasePawn::BeginPlay()
{
	Super::BeginPlay();

	// Change the movement speed
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
	SetStartingHealth();

	if (SoundBase)
	{
		AudioComponent->SetSound(SoundBase);
	}
}

// Called every frame
void ACPP_BasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FName ACPP_BasePawn::GetPawnName() const
{
	return PawnName;
}

float ACPP_BasePawn::GetCurrentHealth() const
{
	return CurrentHealth;
}

float ACPP_BasePawn::GetMaxHealth() const
{
	return MaxHealth;
}

FVector ACPP_BasePawn::GetSpawnLocation() const
{
	return SpawnLocation;
}

bool ACPP_BasePawn::IsAlive() const
{
	return bIsAlive;
}

void ACPP_BasePawn::SetCurrentHealth(float NewCurrentHealth)
{
	CurrentHealth = NewCurrentHealth;
}

void ACPP_BasePawn::SetStartingHealth()
{
	CurrentHealth = MaxHealth;
}

void ACPP_BasePawn::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
}

void ACPP_BasePawn::TakeDamageWhenHit(float DamageValue)
{
	float NewHealth = CurrentHealth - DamageValue;

	SetCurrentHealth(NewHealth);

	bIsAlive = (CurrentHealth > 0 ? true : false);
}

void ACPP_BasePawn::PlaySound()
{
	AudioComponent->Play();
}

void ACPP_BasePawn::PauseSound()
{
	if (!AudioComponent->bIsPaused)
	{
		AudioComponent->SetPaused(true);
	}
	else 
	{
		AudioComponent->SetPaused(false);
	}
}

void ACPP_BasePawn::StopSound()
{
	AudioComponent->Stop();
}

void ACPP_BasePawn::HandleHit(int32 WeaponIdentifier, int32 damage)
{
}


