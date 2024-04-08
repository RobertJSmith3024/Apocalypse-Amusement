// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_FindPlayerLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UCPP_FindPlayerLocation::UCPP_FindPlayerLocation()
{
	NodeName = TEXT("Find Player Location CPP");
}

EBTNodeResult::Type UCPP_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	//Find player location
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	FVector Location = PlayerController->GetPawn()->GetActorLocation();

	//Set player location to blackboard
	AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location);


	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//return EBTNodeResult::Type();
	return EBTNodeResult::Succeeded;
}
