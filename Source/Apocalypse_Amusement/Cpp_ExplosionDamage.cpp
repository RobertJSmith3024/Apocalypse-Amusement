// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_ExplosionDamage.h"
#include "Components/SphereComponent.h"
#include "CPP_Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ACpp_ExplosionDamage::ACpp_ExplosionDamage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a SphereComponent to represent the damage area
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionSphere"));
	RootComponent = SphereComponent;

	SphereComponent->InitSphereRadius(200.0f);
}

// Called when the game starts or when spawned
void ACpp_ExplosionDamage::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(ExplosionLocation);

	// Set Sphere radius
	SphereComponent->SetSphereRadius(CollisionSphereRadius);

	SphereComponent->GetOverlappingActors(OverlappingEnemies, ACPP_Enemy::StaticClass());

	for (AActor* OverlappingActor : OverlappingEnemies)
	{
		ACPP_Enemy* Enemy = Cast<ACPP_Enemy>(OverlappingActor);
		if (Enemy)
		{
			// Add the overlapping actor to the array
			OverlappingEnemies.AddUnique(Enemy);
		}
	}

	// Bind the overlap function
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ACpp_ExplosionDamage::OnOverlapBegin);

	// Start the delayed explosion timer
	GetWorldTimerManager().SetTimer(DelayedExplosionHandle, this, &ACpp_ExplosionDamage::ExecuteExplosion, DelayBeforeExplosion, false);
	// Spawn particle system if provided
	if (ExplosionParticleBlueprint)
	{
		// Spawn Particle effect
		UNiagaraComponent* ParticleSystemComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionParticleBlueprint, GetActorLocation(), FRotator::ZeroRotator);
		if (ParticleSystemComponent)
		{
			// Attach the particle system to the root component (or any other desired component)
			ParticleSystemComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}


// Called every frame
void ACpp_ExplosionDamage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACpp_ExplosionDamage::ExecuteExplosion()
{
	// ERROR ENCOUNTERED HERE DUE TO NULL PTR - Explosion trigger twice in quick succession. If Enemy die when one explosion try to do damage
	// Encounter a null ptr
	for (AActor* OverlappingEnemy : OverlappingEnemies)
	{
		ACPP_Enemy* Enemy = Cast<ACPP_Enemy>(OverlappingEnemy);
		// Check if the actor is of the specified damageable class
		if (Enemy)
		{
			// Calculate the distance from the explosion center
			int32 Distance = FVector::Dist(Enemy->GetActorLocation(), GetActorLocation());

			// Calculate damage based on proximity
			int32 ProximityDamage = FMath::Lerp(MaxDamage, 0.0f, Distance / CollisionSphereRadius);

			// Apply the damage to the actor (you need to implement this function in your damageable actor class
			Enemy->HandleHit(WeaponIdentifier, ProximityDamage);
		}
	}
	// Clear the array after applying damage
	OverlappingEnemies.Empty();

	// Destroy Actor
	Destroy();
}

void ACpp_ExplosionDamage::SetExplosionLocation(FVector newExplosionLocation)
{
	ExplosionLocation = newExplosionLocation;
}

FVector ACpp_ExplosionDamage::GetExplosionLocation()
{
	return ExplosionLocation;
}

void ACpp_ExplosionDamage::SetWeaponIdentifier(int32 newWeaponIdentifier)
{
	WeaponIdentifier = newWeaponIdentifier;
}

void ACpp_ExplosionDamage::SetMaxDamage(int32 newMaxDamage)
{
	MaxDamage = newMaxDamage;
}

int32 ACpp_ExplosionDamage::GetMaxDamage()
{
	return MaxDamage;
}

void ACpp_ExplosionDamage::SetCollisionSphereRadius(float newCollisionSphereRadius)
{
	CollisionSphereRadius = newCollisionSphereRadius;
}

float ACpp_ExplosionDamage::GetCollisionSphereRadius()
{
	return CollisionSphereRadius;
}

void ACpp_ExplosionDamage::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPP_Enemy* Enemy = Cast<ACPP_Enemy>(OtherActor);
	// Check if the actor is of the specified damageable class and hasn't been damaged yet
	UE_LOG(LogTemp, Warning, TEXT("OVERLAP"));
	if (OtherActor && Enemy)
	{
		// Add the overlapping actor to the array
		OverlappingEnemies.AddUnique(Enemy);
	}
}
