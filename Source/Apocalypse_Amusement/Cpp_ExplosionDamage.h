// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cpp_ExplosionDamage.generated.h"

UCLASS()
class APOCALYPSE_AMUSEMENT_API ACpp_ExplosionDamage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACpp_ExplosionDamage();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Explosion")
	void ExecuteExplosion();

	UFUNCTION(BlueprintCallable, Category = "Explosion")

	FVector GetExplosionLocation();

	void SetExplosionLocation(FVector newExplosionLocation);

	void SetWeaponIdentifier(int32 newWeaponIdentifier);

	void SetMaxDamage(int32 newMaxDamage);

	int32 GetMaxDamage();

	void SetCollisionSphereRadius(float newCollisionSphereRadius);

	float GetCollisionSphereRadius();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Explosion")
	class USphereComponent* SphereComponent;

	// Damage properties
	UPROPERTY(EditAnywhere, Category = "Explosion")
	int32 MaxDamage = 50;

	// Radius of the collision sphere // Damage Radius
	UPROPERTY(EditAnywhere, Category = "Explosion")
	float CollisionSphereRadius = 50.0f;

	// Array to store overlapping actors
	TArray<class AActor*> OverlappingEnemies;

	// Timer handle for delaying the explosion
	FTimerHandle DelayedExplosionHandle;

	// Delay before executing explosion (in seconds)
	UPROPERTY(EditAnywhere, Category = "Explosion")
	float DelayBeforeExplosion = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Explosion")
	FVector ExplosionLocation = { 0, 0, 0 };

	// Particle Effect
	UPROPERTY(EditAnywhere, Category = "Explosion")
	class UNiagaraSystem* ExplosionParticleBlueprint;

	int32 WeaponIdentifier;

	// Function to handle overlap events
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
