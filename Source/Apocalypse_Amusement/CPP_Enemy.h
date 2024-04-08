// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_BasePawn.h"
#include "Cpp_Projectile.h"
#include "Components/BoxComponent.h"
#include "CPP_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class APOCALYPSE_AMUSEMENT_API ACPP_Enemy : public ACPP_BasePawn
{
	GENERATED_BODY()
	
public:
	//Enemy default values
	ACPP_Enemy();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Called every frame
	virtual void Tick(float DeltaTime) override;

	//Deal with projectile damage
	void HandleHit(int32 WeaponIdentifier, int32 damage);

	void MeleeAttack_Implementation();

	// Montage
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* MeleeMontage;
	float MeleeMontageLength;

protected:
	// Damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = true))
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability", meta = (AllowPrivateAccess = true))
	FString Ability;

	// Exp that provide to player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exp", meta = (AllowPrivateAccess = true))
	float Exp = 50.f;

	// Melee Attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = true))
	UBoxComponent* MeleeAttackCollisionBox;
	bool bIsAttacking;
	

private:
	//Test for projectile collision
	//UFUNCTION()	virtual void NotifyHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()	virtual void OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};

//AI, Damage, Ability, AIController