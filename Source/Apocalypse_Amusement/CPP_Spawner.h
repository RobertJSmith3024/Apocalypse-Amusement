// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/TextRenderComponent.h" // Used for spawner label
#include "Styling/CoreStyle.h" // Used for spawner label font setting
//#include "CPP_AIController.h"
#include "CPP_Enemy.h"

#include "CPP_Spawner.generated.h"

UCLASS()
class APOCALYPSE_AMUSEMENT_API ACPP_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Spawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The type of item that should be spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<class ACPP_Enemy> enemyBlueprint;	

	// Duration between each spawn event in seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float spawnInterval = 5; 

	// Range around the spawn point that items should be spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float spawnRadius = 200.f;

	// Boolean to set spawn point active or not
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	bool bIsSpawnerActive = true; // Note: "bIsSpawnable" identifier not used as would cause conflict with SequenceBindingTree.h

	// Label the spawner
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	UTextRenderComponent* spawnLabel;
 
	// Boolean to set the spawn label visible in game
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHiddenInGame;

	// Vertical height of spawn label over spawner
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float spawnLabelVerticalOffset;

	// Range around the spawn point that items should be spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float ZombieHealth = 100;

private:
	// Spawn timer to countdown to next spawn event
	float spawnTimer;

	// Game State class
	class ACPP_GameState* CPPGameState;

	void Spawn();

};
