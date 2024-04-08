// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_InMeleeRange.generated.h"

/**
 * 
 */
UCLASS()
class APOCALYPSE_AMUSEMENT_API UBTService_InMeleeRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_InMeleeRange();

	//void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	float MeleeRange = 90.f;
	
};
