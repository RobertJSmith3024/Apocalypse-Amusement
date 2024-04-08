// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cpp_Projectile.generated.h"

UCLASS()
class APOCALYPSE_AMUSEMENT_API ACpp_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACpp_Projectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	int32 getDamage();

	UFUNCTION(BlueprintCallable)
	void setDamage(int32 damage);

	void setParentWeaponIdentifier(int32 WeaponIdentifier);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* ArrowComponent;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjectileComponent;

	UPROPERTY(EditAnywhere)
	float DesiredXVelocity = 300;


private:
	int32 Damage;

	int32 ParentWeaponIdentifier;

	// Sphere collision component
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class UBoxComponent* CollisionComponent;

	UFUNCTION()
	virtual void OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
