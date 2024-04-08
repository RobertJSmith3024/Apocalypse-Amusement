// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cpp_XpTest.generated.h"

UCLASS()
class APOCALYPSE_AMUSEMENT_API ACpp_XpTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACpp_XpTest();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int32 GetXP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere);
	int32 XP;



};
