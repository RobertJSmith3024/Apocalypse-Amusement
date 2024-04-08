// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_XpTest.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ACpp_XpTest::ACpp_XpTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMesh;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACpp_XpTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACpp_XpTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ACpp_XpTest::GetXP()
{
	return XP;
}

