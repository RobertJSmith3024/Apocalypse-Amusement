// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeleeAttack.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/LatentActionManager.h"
#include "CPP_AIController.h"
#include "CPP_Enemy.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
	NodeName = "Melee Attack";
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bool OutOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	// Do nothing if out of melee range
	if (OutOfRange)
	{
		// finish the task
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	auto* AIController = Cast<ACPP_AIController>(OwnerComp.GetAIOwner());
	auto* AICharacter = Cast<ACPP_Enemy>(AIController->GetPawn());
	if (AICharacter)
	{
		if (MontageHasFinished(AICharacter))
		{
			AICharacter->MeleeAttack_Implementation();
			// finish the task
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
	
}

bool UBTTask_MeleeAttack::MontageHasFinished(auto* const AIPawn)
{
	return AIPawn->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(AIPawn->GetCurrentMontage());
}
