// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Kismet/GameplayStatics.h" //For FObjectInitializer and ExecuteTask
#include "NavigationSystem.h" //For UNavigationSystemV1::GetCurrent(GetWorld())
#include "CPP_Player.h" //For Player
#include "BehaviorTree/BlackboardComponent.h" //For GetBlackboardComponent
#include "BTTask_SeekPlayerLocation.generated.h"

/**
 * Non-exact search for the player, using a random deviation to direct AI to general area, not a point.
 */
UCLASS()
class APOCALYPSE_AMUSEMENT_API UBTTask_SeekPlayerLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_SeekPlayerLocation(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta=(AllowPrivateAccess="true"))
	bool SearchRandom = false; // Search random area around player toggle

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta=(AllowPrivateAccess="true"))
	float SearchRadius = 150.f; // Search radius around player



};
