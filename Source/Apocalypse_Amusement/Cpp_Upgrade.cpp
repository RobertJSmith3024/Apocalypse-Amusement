// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_Upgrade.h"
#include "CPP_Player.h"

// Sets default values
ACpp_Upgrade::ACpp_Upgrade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACpp_Upgrade::BeginPlay()
{
	Super::BeginPlay();
	SetMaxLevel(MaxLevel);
	
}

// Called every frame
void ACpp_Upgrade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACpp_Upgrade::Upgrade(int upgradeLevel)
{
	// Upgrade Level++. Remove need for input and just pass in switch statement
}

void ACpp_Upgrade::AttachToPlayer(ACPP_Player* Player)
{

}

void ACpp_Upgrade::PrimaryFire()
{
}

void ACpp_Upgrade::SecondaryFire()
{
}

int32 ACpp_Upgrade::GetUpgradeLevel()
{
	return Level;
}

void ACpp_Upgrade::SetUpgradeLevel(int32 newLevel)
{
	Level = newLevel;
}

int32 ACpp_Upgrade::GetMaxLevel()
{
	return MaxLevel;
}

void ACpp_Upgrade::SetMaxLevel(int32 setMaxLevel)
{
	MaxLevel = setMaxLevel;
}

FString ACpp_Upgrade::GetName()
{
	return Name;
}

void ACpp_Upgrade::SetName(FString newName)
{
	Name = newName;
}

FString ACpp_Upgrade::GetDescription()
{
	return Description;
}

void ACpp_Upgrade::SetDescription(FString newDescription)
{
	Description = newDescription;
}

float ACpp_Upgrade::GetTotalDamage()
{
	return TotalDamage;
}

void ACpp_Upgrade::AddTotalDamage(float addDamage)
{
	TotalDamage += addDamage;
}

void ACpp_Upgrade::SetTotalDamage(int32 newTotalDamage)
{
	TotalDamage = newTotalDamage;
}

float ACpp_Upgrade::GetTotalKills()
{
	return TotalKills;
}

void ACpp_Upgrade::AddTotalKills()
{
	TotalKills += TotalKills;
}

void ACpp_Upgrade::SetWeaponIdentifier(int32 newWeaponIdentifier)
{
	WeaponIdentifier = newWeaponIdentifier;
}

