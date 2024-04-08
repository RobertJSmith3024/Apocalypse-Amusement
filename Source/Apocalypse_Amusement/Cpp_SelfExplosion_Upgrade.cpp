// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_SelfExplosion_Upgrade.h"
#include "Components/BoxComponent.h"   // Include for UBoxComponent
#include "CPP_Enemy.h"
#include "Cpp_ExplosionDamage.h"
#include "CPP_Player.h"

ACpp_SelfExplosion_Upgrade::ACpp_SelfExplosion_Upgrade()
{
	// Create the default scene root and set it as the root component
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	// Create the collision box and attach it to the root component
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(DefaultSceneRoot);
}

void ACpp_SelfExplosion_Upgrade::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACpp_SelfExplosion_Upgrade::OnEnemyCollision);
}

void ACpp_SelfExplosion_Upgrade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACpp_SelfExplosion_Upgrade::Upgrade(int upgradeLevel)
{
    switch (upgradeLevel)
    {
    case 1:
        MaxDamage = 100;
        ExplosionRadius = 50;
        ExplosionCooldown = 60;
        // Set description for next upgrade
        Description = "";
        break;

    case 2:
        MaxDamage = 150;
        ExplosionRadius = 100;
        ExplosionCooldown = 45;
        Description = "";
        break;

    case 3:
        MaxDamage = 200;
        ExplosionRadius = 150;
        ExplosionCooldown = 30;
        Description = "";
        break;

    case 4:
        MaxDamage = 200;
        ExplosionRadius = 200;
        ExplosionCooldown = 25;
        Description = "";
        break;

    case 5:
        MaxDamage = 300;
        ExplosionRadius = 250;
        ExplosionCooldown = 20;
        Description = "";
        break;

    case 6:
        MaxDamage = 350;
        ExplosionRadius = 300;
        ExplosionCooldown = 15;
        Description = "";
        break;

    case 7:
        MaxDamage = 500;
        ExplosionRadius = 500;
        ExplosionCooldown = 10;
        Description = "";
        break;

    default:
        // Handle unexpected upgrade level
        break;
    }
    // Reset Timer on Self Explosion
    ResetTrigger();
}

void ACpp_SelfExplosion_Upgrade::AttachToPlayer(ACPP_Player* Player)
{
    // Attach to Skeletal mesh
    USkeletalMeshComponent* PlayerMesh = Player->GetMesh();
    if (PlayerMesh)
    {
        this->AttachToComponent(PlayerMesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
        // Set relative rotation (adjust these values as needed)
        this->SetActorRelativeRotation(FRotator(3.5, -80.5, 200));
    }
}

void ACpp_SelfExplosion_Upgrade::SpawnExplosion()
{
	if (bTriggered == true)
	{
		return;
	}
	FTransform ParentActorTransform = GetTransform();
	ACpp_ExplosionDamage* NewExplosion = GetWorld()->SpawnActorDeferred<ACpp_ExplosionDamage>(ExplosionActor, ParentActorTransform);
	if (NewExplosion)
	{
		NewExplosion->SetMaxDamage(MaxDamage);
		NewExplosion->SetCollisionSphereRadius(ExplosionRadius);
        NewExplosion->SetWeaponIdentifier(WeaponIdentifier);
		NewExplosion->SetExplosionLocation(GetActorLocation());
		NewExplosion->FinishSpawning(ParentActorTransform);
	}

	bTriggered = true;
	GetWorldTimerManager().SetTimer(ExplosionCooldownHandle, this, &ACpp_SelfExplosion_Upgrade::ResetTrigger, ExplosionCooldown, false);
}

void ACpp_SelfExplosion_Upgrade::ResetTrigger()
{
	bTriggered = false;
	GetWorldTimerManager().ClearTimer(ExplosionCooldownHandle); // Optional: Clear the timer
}

void ACpp_SelfExplosion_Upgrade::OnEnemyCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("COLLISION"));

	//Is other actor able to be XPTest? If so then store in XPTest for future use
	ACPP_Enemy* Enemy = Cast<ACPP_Enemy>(OtherActor);
	//Only execute if colliding with XPTest
	if (Enemy != nullptr)
	{
		SpawnExplosion();
	}
}