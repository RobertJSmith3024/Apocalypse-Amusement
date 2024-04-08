// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "CPP_Log.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Random Location in NavMesh";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get AI controller and attached enemy
	if (AAIController* const controller = Cast<AAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const aiEnemy = controller->GetPawn())
		{
			// Obtain location to use as an origin
			auto const Origin = aiEnemy->GetActorLocation();
			// Get a random location from the navigation system
			if (auto* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation position;
				if (NavSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, position))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), position.Location);
				}

				/*
				//Log class test
				CPP_Log::Log(SLog::INFO, "Random Location passed to Blackboard! A", 3);
				CPP_Log::Log(SLog::WARN, "Default log message duration");
				CPP_Log::Log(SLog::ERROR, "Default log message type", 3);
				CPP_Log::Log(); //OTHER type default
				*/

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;

			}

		}
	}
	
	return EBTNodeResult::Failed;
}
