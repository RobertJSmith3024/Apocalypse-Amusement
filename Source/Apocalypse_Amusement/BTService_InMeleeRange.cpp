// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_InMeleeRange.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "CPP_AIController.h"
#include "CPP_BasePawn.h"
#include "CPP_Player.h"
#include "CPP_Enemy.h"

UBTService_InMeleeRange::UBTService_InMeleeRange()
{
	/*bNotifyBecomeRelevant = true;*/
	NodeName = "Is Player In Melee Range";
}

//void UBTService_InMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//	// Get AI and player reference 
//	auto* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());
//	if (AIController)
//	{
//		auto* AIPawn = Cast<ACPP_Enemy>(AIController->GetPawn());
//		/*UE_LOG(LogTemp, Warning, TEXT("%s"), AIController->GetPawn()->GetFName());*/
//		auto* Player = Cast<ACPP_BasePawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
//		if (AIPawn)
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Service_IsMeleeRange: AIPawn exists"));
//		}
//		if (Player)
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Service_IsMeleeRange: PlayerPawn exists"));
//		}
//		if (AIPawn && Player)
//		{
//			// check if the distance between player and ai is larger than Melee range
//			bool IsInRange = AIPawn->GetDistanceTo(Player) <= MeleeRange;
//
//			// set the result to the selected blackboard key 
//			OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), IsInRange);
//			UE_LOG(LogTemp, Warning, TEXT("Service_IsMeleeRange is working!"));
//		}
//
//	}
//}

void UBTService_InMeleeRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Get AI and player reference 
	auto* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		auto* AIPawn = Cast<ACPP_Enemy>(AIController->GetPawn());

		auto* Player = Cast<ACPP_BasePawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (AIPawn && Player)
		{
			// check if the distance between player and ai is larger than Melee range
			bool IsInRange = AIPawn->GetDistanceTo(Player) <= MeleeRange;

			// set the result to the selected blackboard key 
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), IsInRange);
		/*	UE_LOG(LogTemp, Warning, TEXT("Service_IsMeleeRange is working!"));*/
		}

	}
}
