// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Log.h"


CPP_Log::CPP_Log()
{
    return;
}

CPP_Log::~CPP_Log()
{
	return;
}



void CPP_Log::Log(SLog Type, const FString& Message, const float& Duration)
{
    float LogDuration = Duration;
    FColor LogColor;
    FString LogString;

    switch (Type)
    {
    case SLog::INFO:
        LogColor = FColor::Green;
        LogString = FString::Printf(TEXT("Skyward  INFO: %s"), *Message);
        break;
    case SLog::WARN:
        LogColor = FColor::Yellow;
        LogString = FString::Printf(TEXT("Skyward  WARN: %s"), *Message);
        break;
    case SLog::ERROR:
        LogColor = FColor::Red;
        LogString = FString::Printf(TEXT("Skyward ERROR: %s"), *Message);
        break;
    case SLog::OTHER:
    default:
        LogColor = FColor::Blue;
        LogString = FString::Printf(TEXT("Skyward GENERAL: %s"), *Message);
        break;
        
    }

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, LogDuration, LogColor, LogString);
    }
}
