// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerController.h"
#include "GameFramework/Character.h"
#include <Kismet/KismetMathLibrary.h>
#include "CPP_Player.h"
#include "Kismet/GameplayStatics.h"
#include "CPP_GameMode.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ACPP_PlayerController::ACPP_PlayerController()
{

}

void ACPP_PlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	SetShowMouseCursor(true);
}

void ACPP_PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup look input events
		//EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACPP_PlayerController::Look);

		// Setup move input events
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACPP_PlayerController::Move);
		
		// Setup fire input events
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ACPP_PlayerController::Fire);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &ACPP_PlayerController::StopFire);

		// Setup Pause input events
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ACPP_PlayerController::PauseGame);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACPP_PlayerController::Tick(float DeltaTime)
{
	Look();
}

void ACPP_PlayerController::Move(const FInputActionValue& Value)
{
	FVector MovementVector = Value.Get<FVector>();

	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		// find out which way is forward
		const FRotator Rotation = ControlledPawn->GetControlRotation();

		//const FRotator YawRotation(0, 0, Rotation.Yaw);
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = YawRotation.Vector();

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);

		// add movement
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACPP_PlayerController::Look()
{

	APawn* ControlledPawn = GetPawn();

	if (ControlledPawn != nullptr)
	{
		ACharacter* PlayerCharacter = Cast<ACharacter>(ControlledPawn);
		FHitResult Hit;

		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
		FVector HitLocation = Hit.Location;
		FVector TargetVector = HitLocation - ControlledPawn->GetActorLocation();
		FRotator WorldDirection = (TargetVector).GetSafeNormal().Rotation();

		// Set the pawn rotation to target direction
		ControlledPawn->SetActorRotation(WorldDirection);
	}
}

void ACPP_PlayerController::Fire()
{
	// Debug Text
	//UE_LOG(LogTemp, Warning, TEXT("On Fire"));
	APawn* ControlledPawn = GetPawn();

	if (ControlledPawn != nullptr)
	{
		bIsFiring = true;
		ACPP_Player* PlayerCharacter = Cast<ACPP_Player>(ControlledPawn);
		if (bIsReadyFiring)
		{
			PlayerCharacter->ShootWeapon();
		}
		
	}
}

void ACPP_PlayerController::StopFire()
{
	bIsFiring = false;
	bIsReadyFiring = false;
	//UE_LOG(LogTemp, Warning, TEXT("Stop Fire"));
}

void ACPP_PlayerController::PauseGame()
{
	ACPP_GameMode* GameMode = Cast<ACPP_GameMode>(GetWorld()->GetAuthGameMode());
	GameMode->StartPauseGameState();
}
