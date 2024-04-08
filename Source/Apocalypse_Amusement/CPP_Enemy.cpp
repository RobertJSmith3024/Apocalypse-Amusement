// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Enemy.h"
#include "CPP_Player.h"
#include "Engine/EngineTypes.h"

ACPP_Enemy::ACPP_Enemy()
{

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeleeAttackCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	FName SocketName = "Hand_R";
	MeleeAttackCollisionBox->SetupAttachment(GetMesh(), SocketName);
	MeleeAttackCollisionBox->SetBoxExtent(FVector{ 15 }, false);
	MeleeAttackCollisionBox->SetCollisionProfileName("NoCollision");

}

void ACPP_Enemy::BeginPlay()
{
	Super::BeginPlay();

	MeleeAttackCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACPP_Enemy::OnOverlapStart);
	//MeleeAttackCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ACPP_Enemy::OnOverlapStart);
}

void ACPP_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPP_Enemy::HandleHit(int32 WeaponIdentifier, int32 damage)
{
	UE_LOG(LogTemp, Warning, TEXT("CPP_Enemny::HandleHit: Enemy taking damage!"));
	//Handle hit of projectiles
	float health = GetCurrentHealth();
	health -= float(damage);
	auto* Player = Cast<ACPP_Player>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Player->UpdateWeaponDamage(WeaponIdentifier, damage);
	if (health <= 0) { //if enemy has died
		SetCurrentHealth(0);
		if (Player)
		{
			Player->AddCurrentExp(Exp);
			Player->UpdateWeaponKill(WeaponIdentifier, 1);
		}

		Destroy(); // Destroy object i.e. kill enemy
	}
	else
	{
		SetCurrentHealth(health);
	}

}

void ACPP_Enemy::MeleeAttack_Implementation()
{
	if (MeleeMontage)
	{
		MeleeMontageLength = PlayAnimMontage(MeleeMontage);
	}
}

void ACPP_Enemy::OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*UE_LOG(LogTemp, Warning, TEXT("COLLISION with Enemy!"));*/
	//If collision is with a player handle collision
	if (auto* Player = Cast<ACPP_Player>(OtherActor)) {
		if (!bIsAttacking)
		{
			bIsAttacking = true;
			Player->TakeDamageWhenHit(Damage);
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("%f"), Player->GetCurrentHealth()));
			FTimerHandle MeleeTimerHandle;
			FTimerDelegate MeleeTimeDelegate;
			MeleeTimeDelegate.BindLambda([this]()
				{
					bIsAttacking = false;
				});
			GetWorld()->GetTimerManager().SetTimer(MeleeTimerHandle, MeleeTimeDelegate, MeleeMontageLength, false);
		}

	}

}

//void ACPP_Enemy::OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//}


//void ACPP_Enemy::NotifyHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
//{
//    UE_LOG(LogTemp, Warning, TEXT("COLLISION with Enemy!"));
//    // Check if the OtherActor is a projectile
// //HasTag requires "GameplayTags" addition to build.cs
//   // if (OtherActor && OtherActor->ActorHasTag("Projectile")) {
//        // Handle projectile hit (e.g., reduce enemy health, play impact effects)
//        // You can also notify the enemy to react (e.g., take damage, play animations).
//    //}
//}