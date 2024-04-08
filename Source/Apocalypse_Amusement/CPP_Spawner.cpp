// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Spawner.h"
#include "CPP_GameState.h"

// Sets default values
ACPP_Spawner::ACPP_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ACPP_Spawner::spawnTimer = spawnInterval; //Initiate the spawn timer with the spawn interval
	ACPP_Spawner::spawnLabelVerticalOffset = 150.0f; // Set vertical offset of spawn label over spawn point
	ACPP_Spawner::bHiddenInGame = true; // Set spawn label to hidden in game as default

	// Set up the spawner label
	spawnLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Spawner Text Label"));

	// Attach spawner label to root component
	spawnLabel->SetupAttachment(RootComponent);

	// Set spawner label text properties
	spawnLabel->SetText(FText::FromString("Spawn\nPoint"));
	//spawnLabel->SetFont( Cast<UFont*>(GetDefaultFont()) ); // Messy! Requires "static TSharedRef< const FCompositeFont > FCoreStyle::GetDefaultFont()" to be recast as a UFont pointer. No cast for arguments. 
	spawnLabel->SetTextRenderColor(FColor::Red);
	spawnLabel->SetHorizontalAlignment(EHTA_Center);
	spawnLabel->SetVerticalAlignment(EVRTA_TextCenter);

	// Apply vertical offset to spawn label
	FVector Location = spawnLabel->GetRelativeLocation();
	Location.Z += spawnLabelVerticalOffset;
	spawnLabel->SetRelativeLocation(Location);

	// Set the spawn label to be hidden in game
	spawnLabel->SetHiddenInGame(bHiddenInGame);

}

// Called when the game starts or when spawned
void ACPP_Spawner::BeginPlay()
{
	Super::BeginPlay();
	CPPGameState = Cast<ACPP_GameState>(GetWorld()->GetGameState());
	
}

// Called every frame
void ACPP_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsSpawnerActive && CPPGameState->AllowSpawning()) // If spawner is active
	{
		spawnTimer -= DeltaTime; //Decrement timer by time elapsed
		if (spawnTimer < 0.0f) //Time to spawn new actor reached
		{
			if (spawnInterval > 0.1)
			{
				spawnInterval = spawnInterval - 0.01;
				ZombieHealth = ZombieHealth + 2;
			}
			Spawn();
		}
	}
}

void ACPP_Spawner::Spawn()
{
	spawnTimer = spawnInterval; //Reset spawn timer
	UWorld* world = GetWorld();
	if (world)
	{
		FVector thisLocation = this->GetActorLocation(); //Get location reference of this spawn point
		FVector enemyLocation = thisLocation;

		//Find random position within spawn radius
		float randomDistance = FMath::RandRange(0.f, spawnRadius);
		float randomBearing = FMath::DegreesToRadians(FMath::RandRange(0.f, 360.f));
		float randomDistX = FMath::Cos(randomBearing) * randomDistance;
		float randomDistY = FMath::Sin(randomBearing) * randomDistance;

		//Set spawn position to random location
		enemyLocation.X += randomDistX;
		enemyLocation.Y += randomDistY;
		FTransform SpawnTransform(FRotator::ZeroRotator, enemyLocation);
		ACPP_Enemy* enemy = world->SpawnActorDeferred<ACPP_Enemy>(enemyBlueprint, SpawnTransform);
		if (true)
		{
			enemy->SetCurrentHealth(ZombieHealth);
			enemy->SetMaxHealth(ZombieHealth);
			enemy->FinishSpawning(SpawnTransform);
		}
	}
}

