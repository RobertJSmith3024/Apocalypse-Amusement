// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_Weapon.h"
#include "Cpp_Projectile.h"
#include "TimerManager.h"
#include "CPP_Player.h"

ACpp_Weapon::ACpp_Weapon()
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	RootComponent = SkeletalMeshComponent;
}

void ACpp_Weapon::BeginPlay()
{
	Super::BeginPlay();
	SetRateOfFire(RateOfFire);
    SetCurrentAmmo(MaxAmmo);

}

void ACpp_Weapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


void ACpp_Weapon::SpawnProjectile()
{
	if (ProjectileActor == nullptr || !bCanFire || bReloading)
	{
		return;
	}

	// Guard: Check if the SkeletalMeshComponent is valid
	if (SkeletalMeshComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SkeletalMeshComponent is not valid in ACpp_Weapon::SpawnProjectile"));
		return;
	}

	// Guard: Check if the socket with the given name exists
	if (!SkeletalMeshComponent->DoesSocketExist(BulletSocket))
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket %s does not exist on SkeletalMeshComponent in ACpp_Weapon::SpawnProjectile"), *BulletSocket.ToString());
		return;
	}

	// Get the location and rotation of the weapon socket to fire bullet from
	//FTransform SocketTransform = SkeletalMeshComponent->GetSocketTransform(BulletSocket, ERelativeTransformSpace::RTS_World);
    FRotator BulletRotation = FRotator(0, SkeletalMeshComponent->GetSocketRotation(BulletSocket).Yaw, 0);
    FVector BulletTranslation = SkeletalMeshComponent->GetSocketLocation(BulletSocket);
    FTransform SocketTransform = FTransform(BulletRotation, BulletTranslation, FVector(1));

	// Spawn the projectile and set projectile damage
    ACpp_Projectile* NewProjectile = GetWorld()->SpawnActorDeferred<ACpp_Projectile>(ProjectileActor, SocketTransform);
    if (NewProjectile)
    {
        NewProjectile->setDamage(Damage);
        NewProjectile->setParentWeaponIdentifier(WeaponIdentifier);
        NewProjectile->FinishSpawning(SocketTransform);

        UE_LOG(LogTemp, Warning, TEXT("Projectile Velocity: %s"), *NewProjectile->GetVelocity().ToString());
    }
	
    //UE_LOG(LogTemp, Warning, TEXT("Damage: %d"), projDamage);
	bCanFire = false;
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ACpp_Weapon::ResetFire, FireRateTimer, false);
    // Calculate new ammo    
    CurrentAmmo = CurrentAmmo - 1;
    if (CurrentAmmo <= 0)
    {
        Reload();
    }
}

void ACpp_Weapon::Upgrade(int upgradeLevel)
{
    switch (upgradeLevel)
    {
    case 1:
        RateOfFire = 2.0f;  // 2 bullets per second
        Damage = 30;        // 10 damage per bullet
        MaxAmmo = 100;      // Ammo capacity 100
        // Set description for next upgrade
        Description = "";
        break;

    case 2:
        RateOfFire = 2.0f;
        Damage = 40;
        MaxAmmo = 125;
        Description = "";
        break;

    case 3:
        RateOfFire = 3.0f;
        Damage = 50;
        MaxAmmo = 125;
        Description = "";
        break;

    case 4:
        RateOfFire = 3.0f;
        Damage = 60;
        MaxAmmo = 125;
        Description = "";
        break;

    case 5:
        RateOfFire = 4.0f;
        Damage = 70;
        MaxAmmo = 150;
        Description = "";
        break;

    case 6:
        RateOfFire = 4.0f;
        Damage = 80;
        MaxAmmo = 300;
        Description = "";
        break;

    case 7:
        RateOfFire = 5.0f;
        Damage = 100;
        MaxAmmo = 500;
        Description = "";
        break;

    default:
        // Handle unexpected upgrade level
        break;
    }

    SetRateOfFire(RateOfFire);
    SetCurrentAmmo(MaxAmmo);

    // Common logic for all upgrade levels can go here
    // For example, play a sound, update visuals, etc.
}

void ACpp_Weapon::AttachToPlayer(ACPP_Player* Player)
{
    // Attach to Skeletal mesh
    USkeletalMeshComponent* PlayerMesh = Player->GetMesh();
    if (PlayerMesh)
    {
        this->AttachToComponent(PlayerMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
        // Set relative rotation (adjust these values as needed)
        this->SetActorRelativeRotation(FRotator(3.5, -80.5, 200));
    }
}

void ACpp_Weapon::PrimaryFire()
{
    SpawnProjectile();
}

void ACpp_Weapon::SecondaryFire()
{
}

void ACpp_Weapon::SetRateOfFire(float NewRateOfFire)
{
	RateOfFire = NewRateOfFire;
	CalculateFireRateTimer();
}

void ACpp_Weapon::CalculateFireRateTimer()
{
	FireRateTimer = 1 / RateOfFire;
}

void ACpp_Weapon::Reload()
{
    StartReloadProgress();
    bReloading = true;
    GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &ACpp_Weapon::ResetReload, ReloadSpeed, false);
    SetCurrentAmmo(MaxAmmo);
}

void ACpp_Weapon::StartReloadProgress()
{
    // Set the initial progress to 1.0 (fully loaded)
    CurrentReloadProgress = 1.0f;

    // Set up the timer to update the progress every second
    GetWorldTimerManager().SetTimer(ReloadProgressTimeHandle, this, &ACpp_Weapon::UpdateReloadProgress, 1.0f, true);
}

void ACpp_Weapon::UpdateReloadProgress()
{
    // Update the progress based on the remaining time
    CurrentReloadProgress = FMath::Max(0.0f, CurrentReloadProgress - (1.0f / ReloadSpeed));
    // Check if the reload is complete
    if (CurrentReloadProgress <= 0.0f)
    {
        // Reset the progress and stop the timer
        CurrentReloadProgress = 0.0f;
        GetWorldTimerManager().ClearTimer(ReloadProgressTimeHandle);
    }
}

void ACpp_Weapon::SetCurrentAmmo(int32 ammo)
{
    CurrentAmmo = ammo;
}

int32 ACpp_Weapon::GetCurrentAmmo()
{
    return CurrentAmmo;
}

void ACpp_Weapon::SetMaxAmmo(int32 maxAmmo)
{
    MaxAmmo = maxAmmo;
}

int32 ACpp_Weapon::GetMaxAmmo()
{
    return MaxAmmo;
}

// Add a ResetFire function to reset the fire ability after the cooldown
void ACpp_Weapon::ResetFire()
{
	bCanFire = true;
	GetWorldTimerManager().ClearTimer(FireRateTimerHandle); // Optional: Clear the timer
}

void ACpp_Weapon::ResetReload()
{
    bReloading = false;
    GetWorldTimerManager().ClearTimer(ReloadTimerHandle); // Optional: Clear the timer
}


