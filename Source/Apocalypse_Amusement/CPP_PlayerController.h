// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Templates/SubclassOf.h"
#include "InputActionValue.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "CPP_PlayerController.generated.h"


/**
 * 
 */
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);


UCLASS()
class APOCALYPSE_AMUSEMENT_API ACPP_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACPP_PlayerController();

	// Variable to store button state for animation
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	bool bIsFiring;
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	bool bIsReadyFiring;

protected:
	virtual void BeginPlay();

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaTime) override;

private:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;

	/** Pause Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

	void Move(const FInputActionValue& Value);

	void Look();

	void Fire();

	void StopFire();

	void PauseGame();
};
