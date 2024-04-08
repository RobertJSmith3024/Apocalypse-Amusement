// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cpp_Upgrade.h"
#include "Cpp_SelfExplosion_Upgrade.generated.h"

/**
 * 
 */
UCLASS()
class APOCALYPSE_AMUSEMENT_API ACpp_SelfExplosion_Upgrade : public ACpp_Upgrade
{
	GENERATED_BODY()
	
public:
	ACpp_SelfExplosion_Upgrade();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Upgrade(int upgradeLevel) override;

	void AttachToPlayer(class ACPP_Player* Player) override;

	void SpawnExplosion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* DefaultSceneRoot; // Declare a USceneComponent

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionBox; // Declare a UBoxComponent

	// Explosion Properties
	UPROPERTY(EditAnywhere)
	int32 MaxDamage;

	UPROPERTY(EditAnywhere)
	float ExplosionRadius;

	// Timer handle for the explosion
	FTimerHandle ExplosionTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class ACpp_ExplosionDamage> ExplosionActor;

	// Bool and timers for cooldown
	bool bTriggered = false;

	// In Seconds
	UPROPERTY(EditAnywhere)
	float ExplosionCooldown = 60.0f;

	// Timer handle for delaying the explosion
	FTimerHandle ExplosionCooldownHandle;

	void ResetTrigger();

	UFUNCTION()
	void OnEnemyCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
