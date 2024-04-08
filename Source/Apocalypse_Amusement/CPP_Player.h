// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_BasePawn.h"
#include "Cpp_LevelUpWidget.h"

#include "CPP_Player.generated.h"


USTRUCT(BlueprintType)
struct FWeaponInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACpp_Upgrade* WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WeaponLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WeaponIdentifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool WeaponCarried;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WeaponDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WeaponKill;

};

UCLASS()
class APOCALYPSE_AMUSEMENT_API ACPP_Player : public ACPP_BasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// ACCESSOR
	int GetCurrentLevel();
	int GetMaxLevel();

	// Add Exp to current exp
	void AddCurrentExp(float AddExp);

	// Check whether the exp is enough to level up
	bool IsExpEnoughToLevelUp();

	// Check whether the level reaches the max 
	bool IsLevelMax();

	// Level up function when gained enough XP
	UFUNCTION(BlueprintCallable)
	void LevelUp();
	
	// Reset and adjust the exp and expPerLevel
	void ResetExp();

	// Shoot Weapon
	void ShootWeapon();

	// Array to store strucy weapon Info members
	UPROPERTY(EditAnywhere)
	TArray<FWeaponInfo> WeaponInfos;


	void AddUpgradeToInventory();

	// TO BE REMOVED
	void UpdateWeaponDamage(int32 Identifier, int32 WeaponDamage);

	void UpdateWeaponKill(int32 Identifier, int32 WeaponKill);


private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level", meta = (AllowPrivateAccess = "true"))
	int MaxLevel = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level", meta = (AllowPrivateAccess = "true"))
	int CurrentLevel;

	// Exp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exp", meta = (AllowPrivateAccess = "true"))
	float CurrentExp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exp", meta = (AllowPrivateAccess = "true"))
	float ExpRequiredPerLevel;
	// Health to add to MaxHP upon levelling
	UPROPERTY(EditAnywhere, Category = "Health")
	int32 HealthPerLevel = 50;

	// InventorySlots
	int32 MaxUpgrades = 3;
	int32 CurrentUpgrades = 0;



	//For testing pickup XP
	UFUNCTION()
	virtual void OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//AI Perception components
	class UAIPerceptionStimuliSourceComponent* StimulusSource;
	void SetupStimulusSource();







	// New attempt at Upgrade System
	// Array to store struct of Weapons - Holds Weapon name and Subclass

	class ACpp_Upgrade* StartingUpgrade;

	UPROPERTY(EditAnywhere, Category = "Upgrades")
	TSubclassOf<class ACpp_Upgrade> StartingUpgradeClass;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ACpp_Upgrade>> WeaponsTwo;

	// Map to track and store Spawned Upgrades pointers
	TMap<TSubclassOf<ACpp_Upgrade>, ACpp_Upgrade*> SpawnedUpgradesMap;

	TArray<TSubclassOf<ACpp_Upgrade>> GetRandomUpgrade(int32 NumUpgradesToRetrieve);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCpp_DisplayUpgradeWidget> DisplayWidget;

public:
	TMap<TSubclassOf<ACpp_Upgrade>, ACpp_Upgrade*> GetTmap();

	void CreateUpgradeWidget();

	void SpawnStartingUpgrade(TSubclassOf<ACpp_Upgrade> UpgradeClass);

	// Function to call spawn upgrade function
	void OnUpgradeSelected(TSubclassOf<ACpp_Upgrade> UpgradeClass);
	
	// Function to spawn upgrades
	void SpawnUpgrade(TSubclassOf<ACpp_Upgrade> UpgradeSubClass);

};