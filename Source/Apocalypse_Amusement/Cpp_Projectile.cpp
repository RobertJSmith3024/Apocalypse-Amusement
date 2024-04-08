// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "CPP_Enemy.h"

// Sets default values
ACpp_Projectile::ACpp_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Use a box as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = CollisionComponent;
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	
	FVector InitialVelocity = FVector(DesiredXVelocity, 0.0f, 0.0f); // Set X component to your desired value, Y and Z to 0
	ProjectileComponent->Velocity = InitialVelocity;

	ProjectileComponent->bRotationFollowsVelocity = true;

	// Disable gravity for the projectile
	ProjectileComponent->ProjectileGravityScale = 0.0f;
	// Set the maximum simulation time for the projectile (e.g., 5 seconds)
	SetLifeSpan(5.0f);

	// Create and attach the arrow component
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);
}


// Called when the game starts or when spawned
void ACpp_Projectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACpp_Projectile::OnOverlapStart);
	
}

// Called every frame
void ACpp_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ACpp_Projectile::getDamage()
{
	return Damage;
}

void ACpp_Projectile::setDamage(int32 damage)
{
	Damage = damage;
}

void ACpp_Projectile::setParentWeaponIdentifier(int32 WeaponIdentifier)
{
	ParentWeaponIdentifier = WeaponIdentifier;
}

void ACpp_Projectile::OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Check if collision is with Enemy, If Enemy - deal Damage. After If, destroy so that will destroy on any collision.
	
	//Is other actor able to be Enemy? If so then store in Enemy for future use
	ACPP_Enemy* Enemy = Cast<ACPP_Enemy>(OtherActor);

	//Only execute if colliding with EnemyOne
	if (Enemy != nullptr)
	{
		//Call HandleHit function on Enemy so that Enemy can take damage
		Enemy->HandleHit(ParentWeaponIdentifier, Damage);
		//Debugging to test if damage is being passed Correctly
		UE_LOG(LogTemp, Warning, TEXT("Damage: %d"), Damage);
		//Destroy Projectile
		Destroy();
	}
}


