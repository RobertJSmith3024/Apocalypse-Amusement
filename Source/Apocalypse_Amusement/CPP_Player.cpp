// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Player.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Cpp_Weapon.h"
#include "Cpp_SelfExplosion_Upgrade.h"
#include "Cpp_XpTest.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h" // AI Perception component
#include "Perception/AISense_Sight.h" // AI Perception component
#include "Cpp_DisplayUpgradeWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACPP_Player::ACPP_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Set up the default health
	ACPP_BasePawn::MaxHealth = 100;
	ACPP_BasePawn::CurrentHealth = ACPP_BasePawn::MaxHealth;

	// Set up the default exp;
	CurrentExp = 0.f;
	ExpRequiredPerLevel = 100.f;

	// Set up the default player level
	CurrentLevel = 1;

	// AI Perception component
	SetupStimulusSource();

}

// Called when the game starts or when spawned
void ACPP_Player::BeginPlay()
{
	Super::BeginPlay();

	//Collision for testing XP
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACPP_Player::OnOverlapStart);
	
	// Spawn Starting Upgrade
	SpawnStartingUpgrade(StartingUpgradeClass);

}

// Called every frame
void ACPP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int ACPP_Player::GetCurrentLevel()
{
	return CurrentLevel;
}

int ACPP_Player::GetMaxLevel()
{
	return MaxLevel;
}

void ACPP_Player::AddCurrentExp(float AddExp)
{
	CurrentExp += AddExp;
	// If enough Xp to level up, call LevelUp function
	if (IsExpEnoughToLevelUp() && !IsLevelMax())
	{
		LevelUp();
	}
}

bool ACPP_Player::IsExpEnoughToLevelUp()
{
	return CurrentExp >= ExpRequiredPerLevel;
}

bool ACPP_Player::IsLevelMax()
{
	return CurrentLevel >= MaxLevel;
}

void ACPP_Player::LevelUp()
{
	CurrentLevel++;

	// Upgrade the health
	// linearly increase by x amount (e.g. 50)
	float NewHealth = ACPP_BasePawn::MaxHealth + HealthPerLevel;
	ACPP_BasePawn::SetMaxHealth(NewHealth);
	ACPP_BasePawn::SetCurrentHealth(ACPP_BasePawn::MaxHealth); // Replenish to max health 

	// Call Upgrade function

	// Call Reset the xp 
	ResetExp();

	//OpenLevelUpWidget();

	CreateUpgradeWidget();

}

void ACPP_Player::ResetExp()
{
	CurrentExp -= ExpRequiredPerLevel; // Keep the excess experience
	ExpRequiredPerLevel *= 1.1; // To be updated after difficulty added. Add a switch function e.g. EDifficulty::Easy, *1.1, Medium, *1.5, Hard, *2
}

void ACPP_Player::ShootWeapon()
{
	if (StartingUpgrade == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Equipped Weapon is NULL"));
		return;
	}
	StartingUpgrade->PrimaryFire();
}

void ACPP_Player::AddUpgradeToInventory()
{
	CurrentUpgrades++;
}

// To be moved to Upgrade class >>
void ACPP_Player::UpdateWeaponDamage(int32 Identifier, int32 WeaponDamage)
{
	// Move to Weapon
	//WeaponInfos[Identifier].WeaponDamage += WeaponDamage;
}
// To be removed
void ACPP_Player::UpdateWeaponKill(int32 Identifier, int32 WeaponKill)
{
	// Move to Weapon
	//WeaponInfos[Identifier].WeaponKill += WeaponKill;
}
// To be moved to Upgrade class <<

void ACPP_Player::OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("COLLISION"));
	//Is other actor able to be XPTest? If so then store in XPTest for future use
	ACpp_XpTest* XPTest = Cast<ACpp_XpTest>(OtherActor);
	//Only execute if colliding with XPTest
	if (XPTest != nullptr)
	{
		AddCurrentExp(XPTest->GetXP());
		UE_LOG(LogTemp, Warning, TEXT("%d"), CurrentLevel);
	}
}

// AI Perception component
void ACPP_Player::SetupStimulusSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (StimulusSource)
	{
		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSource->RegisterWithPerceptionSystem();
	}
}

TArray<TSubclassOf<ACpp_Upgrade>> ACPP_Player::GetRandomUpgrade(int32 NumUpgradesToRetrieve)
{
	TArray<TSubclassOf<ACpp_Upgrade>> RandomUpgrades;

	// Make sure the array of weapons is not empty
	if (WeaponsTwo.Num() > 0)
	{
		// Ensure the number of upgrades to retrieve is not greater than the array size
		NumUpgradesToRetrieve = FMath::Min(NumUpgradesToRetrieve, WeaponsTwo.Num());

		// Use a set to keep track of selected indices
		TSet<int32> RandomIndices;
		int32 UpgradeLevel;
		int32 MaxUpgradeLevel;

		// Loop until we have enough unique indices
		while (RandomIndices.Num() < NumUpgradesToRetrieve)
		{
			int32 RandomIndex = FMath::RandRange(0, WeaponsTwo.Num() - 1);

			// Check if an instance of this subclass has already been spawned
			TSubclassOf<ACpp_Upgrade> UpgradeClass = WeaponsTwo[RandomIndex];
			ACpp_Upgrade** SpawnedUpgrade = SpawnedUpgradesMap.Find(UpgradeClass);
			
			// Logic here to check max level etc.
			if (SpawnedUpgrade && *SpawnedUpgrade)
			{
				UpgradeLevel = (*SpawnedUpgrade)->GetUpgradeLevel();
				MaxUpgradeLevel = (*SpawnedUpgrade)->GetMaxLevel();
			}
			else
			{
				UpgradeLevel = 0;
				MaxUpgradeLevel = 1;
			}

			// Add the index to the set if it's not already included
			if (!RandomIndices.Contains(RandomIndex) && UpgradeLevel < MaxUpgradeLevel)
			{
				RandomIndices.Add(RandomIndex);
				// Add to RandomUpgrades Array
				RandomUpgrades.Add(WeaponsTwo[RandomIndex]);
			}
		}
	}
	// Add extra logic to check that spawned items is less than max carriable items
	return RandomUpgrades;
}

TMap<TSubclassOf<ACpp_Upgrade>, ACpp_Upgrade*> ACPP_Player::GetTmap()
{
	return SpawnedUpgradesMap;
}

void ACPP_Player::CreateUpgradeWidget()
{
	// Spawn an instance of the DisplayWidget class
	UCpp_DisplayUpgradeWidget* DisplayWidgetInstance = CreateWidget<UCpp_DisplayUpgradeWidget>(GetWorld(), DisplayWidget);

	if (DisplayWidgetInstance)
	{
		// Call the DisplayUpgrades function on the instance
		DisplayWidgetInstance->DisplayUpgrades(GetRandomUpgrade(3), this);

		// Add the widget to the viewport so it's visible
		DisplayWidgetInstance->AddToViewport();
	}
}

void ACPP_Player::SpawnStartingUpgrade(TSubclassOf<ACpp_Upgrade> UpgradeClass)
{
	SpawnUpgrade(UpgradeClass);
	WeaponsTwo.Add(UpgradeClass);
	ACpp_Upgrade** UpgradePtr = SpawnedUpgradesMap.Find(UpgradeClass);
	if (UpgradePtr)
	{
		StartingUpgrade = *UpgradePtr;
	}
	else
	{
		// Handle the case where the UpgradeClass is not found in the map
	}
}


// Think about logic from what needs to be fed in here and what needs to be fed through from GetRandomUpgrades function.
void ACPP_Player::OnUpgradeSelected(TSubclassOf<ACpp_Upgrade> UpgradeClass)
{
	if (UpgradeClass)
	{
		// Check if an instance of this subclass has already been spawned
		ACpp_Upgrade** SpawnedUpgrade = SpawnedUpgradesMap.Find(UpgradeClass.Get());

		// If upgrade does not exist - Spawn
		if (!SpawnedUpgrade)
		{
			// If not spawned, then spawn and store the pointer
			SpawnUpgrade(UpgradeClass);
		}
		// If Upgrade exists - Call upgrade function
		else
		{
			int32 UpgradeLevel = (*SpawnedUpgrade)->GetUpgradeLevel();
			int32 NewLevel = UpgradeLevel + 1;
			(*SpawnedUpgrade)->SetUpgradeLevel(NewLevel);
			(*SpawnedUpgrade)->Upgrade(NewLevel);
		}
	}
}

void ACPP_Player::SpawnUpgrade(TSubclassOf<ACpp_Upgrade> UpgradeClass)
{
	// Spawn the upgrade
	ACpp_Upgrade* NewUpgrade = GetWorld()->SpawnActor<ACpp_Upgrade>(UpgradeClass, GetActorTransform());
	SpawnedUpgradesMap.Add(UpgradeClass, NewUpgrade);
	NewUpgrade->AttachToPlayer(this);
}