// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cpp_Upgrade.generated.h"

UCLASS()
class APOCALYPSE_AMUSEMENT_API ACpp_Upgrade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACpp_Upgrade();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void Upgrade(int upgradeLevel);

	UFUNCTION(BlueprintCallable)
	virtual void AttachToPlayer(class ACPP_Player* Player);

	// To be called when Upgrade is starting weapon - Manual firing
	UFUNCTION(BlueprintCallable)
	virtual void PrimaryFire();
	// To be called when Upgrade is a chosen upgrade - Automatic firing
	UFUNCTION(BlueprintCallable)
	virtual void SecondaryFire();

	UFUNCTION(BlueprintCallable)
	int32 GetUpgradeLevel();

	UFUNCTION(BlueprintCallable)
	void SetUpgradeLevel(int32 newLevel);

	UFUNCTION(BlueprintCallable)
	int32 GetMaxLevel();

	UFUNCTION(BlueprintCallable)
	void SetMaxLevel(int32 setMaxUpgradeLevel);

	UFUNCTION(BlueprintCallable)
	FString GetName();

	UFUNCTION(BlueprintCallable)
	void SetName(FString newName);

	UFUNCTION(BlueprintCallable)
	FString GetDescription();

	UFUNCTION(BlueprintCallable)
	void SetDescription(FString newDescription);

	UFUNCTION(BlueprintCallable)
	float GetTotalDamage();

	UFUNCTION(BlueprintCallable)
	void AddTotalDamage(float addDamage);

	UFUNCTION(BlueprintCallable)
	void SetTotalDamage(int32 newTotalDamage);

	UFUNCTION(BlueprintCallable)
	float GetTotalKills();

	UFUNCTION(BlueprintCallable)
	void AddTotalKills();




	// Remove this function
	UFUNCTION(BlueprintCallable)
	void SetWeaponIdentifier(int32 newWeaponIdentifier);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	FString Name;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	int32 Damage;

	int32 Level = 0;

	int32 MaxLevel = 7;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	FString Description;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	FName Socket;

	float TotalDamage;
	int32 TotalKills;

	int32 WeaponIdentifier; // Remove this when fully added new features

	bool bAttachedToPlayer;
private:


};
