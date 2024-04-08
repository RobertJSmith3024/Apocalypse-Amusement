// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CPP_GameState.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGameState : uint8
{
    MainMenu UMETA(DisplayName = "MainMenu"),
    InGame UMETA(DisplayName = "InGame"),
    Pause UMETA(DisplayName = "Pause"),
    Won UMETA(DisplayName = "Won"),
    Loss UMETA(DisplayName = "Loss"),
    None UMETA(DisplayName = "None")
};

UCLASS()
class APOCALYPSE_AMUSEMENT_API ACPP_GameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
    // Constructor
    ACPP_GameState();


public:
    // Variables to store game-related information
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
    float GameTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
    float SurviveTime = 50.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
    bool bIsPlayerAlive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
    EGameState CurrentGameState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
    bool bIsGamePaused;

    //Variables for Player Stat 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
    int32 TotalDamage;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
    int32 TotalKill;

    // Variables for controlling number of enemy on one map
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
    int32 MaxSpawnNumber = 100;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
    int32 CurrentSpawnNumber;
    UFUNCTION(BlueprintCallable)
    bool AllowSpawning();



};
