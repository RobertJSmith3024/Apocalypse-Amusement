// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPP_Player.h"

#include "CPP_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class APOCALYPSE_AMUSEMENT_API ACPP_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACPP_GameMode();

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Current Game State getter and setter
	UFUNCTION(BlueprintPure, Category = "Game State")
	EGameState GetCurrentGameState() const;
	void SetCurrentGameState(EGameState NewState);

	// Player Alive getter and setter
	UFUNCTION(BlueprintPure, Category = "Game State")
	bool GetPlayerAlive() const;
	void SetPlayerAlive(bool bIsAlive);

	// Functions for different game state
	UFUNCTION(BlueprintCallable)
	void StartPauseGameState();
	UFUNCTION(BlueprintCallable)
	void StartEndGameState();

	// Function for pause the game 
	void PauseGame();

	// Reference to the Widget Blueprint class
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetBlueprintClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetBlueprintClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> InGameHUDWidgetBlueprintClass;

	// Function to open Widget
	UFUNCTION(BlueprintCallable, Category = "UI")
	void OpenWidget(TSubclassOf<UUserWidget> Widget);

	// Function to sum up the damage and kill
	void SetTotalDamage(int32 NewDamage);
	void SetTotalKill(int32 NewKill);
	void CalculateTheSum(TArray<FWeaponInfo>* WeaponInfos);
};
