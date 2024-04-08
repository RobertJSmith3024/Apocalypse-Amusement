// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_GameMode.h"
#include "CPP_GameState.h"
#include "CPP_Player.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "CPP_PlayerController.h"

ACPP_GameMode::ACPP_GameMode()
{
	/*GameStateClass = ACPP_GameState::StaticClass();*/
    
}

void ACPP_GameMode::BeginPlay()
{
    Super::BeginPlay();
    FString LevelName = GetWorld()->GetMapName();
    // Print a message to the output log
    //UE_LOG(LogTemp, Warning, TEXT("Game State Changed to %s"), *LevelName);
    if (LevelName == "UEDPIE_0_L_MainMenu")
    {
        SetCurrentGameState(EGameState::MainMenu);
    }
    else
    {
        SetCurrentGameState(EGameState::InGame);
        OpenWidget(InGameHUDWidgetBlueprintClass);
    }
    
}

void ACPP_GameMode::Tick(float DeltaTime)
{
    ACPP_GameState* MyGameState = GetGameState<ACPP_GameState>();
    if (MyGameState)
    {
        FString StateString;
        switch (MyGameState->CurrentGameState)
        {
        case EGameState::MainMenu:
            StateString = "MainMenu";
            break;
        case EGameState::InGame:
            StateString = "InGame";
            MyGameState->GameTime += DeltaTime; // Update GameTime
            StartEndGameState();
            break;
        default:
            StateString = "None";
            break;
        }
        // Print a message to the output log
        /*UE_LOG(LogTemp, Warning, TEXT("Game State Changed to %s"), *StateString);*/
    }
}

EGameState ACPP_GameMode::GetCurrentGameState() const
{
    return GetGameState<ACPP_GameState>()->CurrentGameState;
}

void ACPP_GameMode::SetCurrentGameState(EGameState NewState)
{
    GetGameState<ACPP_GameState>()->CurrentGameState = NewState;
}

bool ACPP_GameMode::GetPlayerAlive() const
{
    return GetGameState<ACPP_GameState>()->bIsPlayerAlive;
}

void ACPP_GameMode::SetPlayerAlive(bool bIsAlive)
{
    GetGameState<ACPP_GameState>()->bIsPlayerAlive = bIsAlive;
}

void ACPP_GameMode::StartPauseGameState()
{
    OpenWidget(PauseWidgetBlueprintClass);
    PauseGame();
}

void ACPP_GameMode::StartEndGameState()
{
    // Get reference to player class
    ACPP_Player* PlayerCharacter = Cast<ACPP_Player>(UGameplayStatics::GetPlayerPawn(this, 0));

    if (PlayerCharacter)
    {
        // if player still survive after the Time limit, won the game, show won screen
        if (PlayerCharacter->GetCurrentHealth() > 0 && GetGameState<ACPP_GameState>()->GameTime >= GetGameState<ACPP_GameState>()->SurviveTime)
        {
            SetCurrentGameState(EGameState::Won);
            CalculateTheSum(&PlayerCharacter->WeaponInfos);
            OpenWidget(GameOverWidgetBlueprintClass);
            PauseGame();
        }
        else if (PlayerCharacter->GetCurrentHealth() <= 0)
        {
            SetCurrentGameState(EGameState::Loss);
            SetPlayerAlive(false);
            CalculateTheSum(&PlayerCharacter->WeaponInfos);
            OpenWidget(GameOverWidgetBlueprintClass);
            PauseGame();
        }
    }

}

void ACPP_GameMode::PauseGame()
{
    APlayerController* const MyPlayer = GetWorld()->GetFirstPlayerController();;
    if (MyPlayer != NULL)
    {
        MyPlayer->SetPause(!MyPlayer->IsPaused());
    }
}

void ACPP_GameMode::OpenWidget(TSubclassOf<UUserWidget> Widget)
{
    // Get the player controller
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    // Check if the Widget Blueprint Class is set
    if (Widget && PlayerController)
    {
        // Create the widget
        UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(PlayerController, Widget);
        // Check if the widget was created successfully
        if (WidgetInstance)
        {
            // Add the widget to the viewport
            WidgetInstance->AddToViewport();
        }
    }
}

void ACPP_GameMode::SetTotalDamage(int32 NewDamage)
{
    GetGameState<ACPP_GameState>()->TotalDamage += NewDamage;
}

void ACPP_GameMode::SetTotalKill(int32 NewKill)
{
    GetGameState<ACPP_GameState>()->TotalKill += NewKill;
}

void ACPP_GameMode::CalculateTheSum(TArray<FWeaponInfo>* WeaponInfos)
{
    for (auto WeaponInfo : *WeaponInfos)
    {
        SetTotalDamage(WeaponInfo.WeaponDamage);
        SetTotalKill(WeaponInfo.WeaponKill);
    }
}


