// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_AIController.h"


ACPP_AIController::ACPP_AIController(FObjectInitializer const& ObjectInitializer)
{
	//Attach Behavior Tree and Blackboard
	BehaviourTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackBoardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));

	SetupPerceptionSystem();

}
void ACPP_AIController::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(BehaviourTree))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Behavior Tree Valid!"));
		RunBehaviorTree(BehaviourTree);
		BehaviourTreeComponent->StartTree(*BehaviourTree);
	}

}

void ACPP_AIController::OnPossess(APawn* InPawn)
{
	//UE_LOG(LogTemp, Warning, TEXT("ACCP_AIController::OnPossess: Enemy AI Possesed"));
	Super::OnPossess(InPawn);
	if (IsValid(Blackboard) && IsValid(BehaviourTree))
	{
		Blackboard->InitializeBlackboard((*BehaviourTree->GetBlackboardAsset()));
	}
}

void ACPP_AIController::SetupPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		SightConfig->SightRadius = 500.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
		SightConfig->PeripheralVisionAngleDegrees = 90.f;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		
		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ACPP_AIController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void ACPP_AIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (auto* const theActor = Cast <ACPP_Player>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
	}
}

/*

// For inclusion in Player class:
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

// For Player.h
private:
	class UAIPerceptionStimuliSourceComponent* StimulusSource;
	void SetupStimulusSource();

// For Player.cpp
	// In constructor
	SetupStimulusSource();

	// Elsewhere
	void ACPP_Player::SetupStimulusSource()
	{
		StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
		if (StimulusSource)
		{
			StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
			StimulusSource->RegisterWithPerceptionSystem();
		}
}
	*/