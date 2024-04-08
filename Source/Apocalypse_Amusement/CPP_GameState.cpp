// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_GameState.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "CPP_Enemy.h"

ACPP_GameState::ACPP_GameState()
{
    GameTime = 0.0f ;
    bIsPlayerAlive = true;
    bIsGamePaused = false;
}

bool ACPP_GameState::AllowSpawning()
{
    TArray<AActor*> FoundEnemy;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPP_Enemy::StaticClass(), FoundEnemy);
    CurrentSpawnNumber = FoundEnemy.Num();
    if (CurrentSpawnNumber < MaxSpawnNumber)
    {
        return true;
    }
    else
    {
        return false;
    }
}


