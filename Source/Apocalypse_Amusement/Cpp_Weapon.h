// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cpp_Upgrade.h"
#include "Cpp_Weapon.generated.h"

/**
 * 
 */
UCLASS()
class APOCALYPSE_AMUSEMENT_API ACpp_Weapon : public ACpp_Upgrade
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACpp_Weapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile();

	// Override Item Upgrade from parent class
	virtual void Upgrade(int upgradeLevel) override;

	void AttachToPlayer(class ACPP_Player* Player) override;

	virtual void PrimaryFire() override;

	virtual void SecondaryFire() override;

	// Current Ammo getter and setter
	UFUNCTION(BlueprintCallable)
	void SetCurrentAmmo(int32 ammo);
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentAmmo();

	// Max Ammo getter and setter
	UFUNCTION(BlueprintCallable)
	void SetMaxAmmo(int32 maxAmmo);
	UFUNCTION(BlueprintCallable)
	int32 GetMaxAmmo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class ACpp_Projectile>ProjectileActor;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	class USkeletalMeshComponent* SkeletalMeshComponent;

	// Rate of Fire functions
	UFUNCTION(BlueprintCallable)
	void SetRateOfFire(float NewRateOfFire);
	void CalculateFireRateTimer();

	// Ammo and Reload Functions
	UFUNCTION(BlueprintCallable)
	void Reload();
	UFUNCTION(BlueprintCallable)
	void StartReloadProgress();
	UFUNCTION(BlueprintCallable)
	void UpdateReloadProgress();

	// Expose the current progress to Blueprints
	UPROPERTY(BlueprintReadOnly, Category = "Weapon", meta=(AllowPrivateAccess = true))
	float CurrentReloadProgress;


private:	
	//Weapon Rate of Fire - Bullets per second - Easier for player to work out and cooler to see.
	UPROPERTY(EditAnywhere, Category = "Weapon")
	float RateOfFire = 2;
	float FireRateTimer;

	//Create variables to spawn bullet location
	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName BulletSocket;
	
	// Ammo and reloading variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo", meta = (AllowPrivateAccess = true))
	float ReloadSpeed = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo", meta = (AllowPrivateAccess = true))
	int32 MaxAmmo = 30;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	int32 CurrentAmmo;

	// For Reloading Timer
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bReloading = false;
	FTimerHandle ReloadTimerHandle;
	FTimerHandle ReloadProgressTimeHandle;
	void ResetReload();

	//for full auto
	bool bCanFire = true;
	FTimerHandle FireRateTimerHandle;
	void ResetFire();

};
