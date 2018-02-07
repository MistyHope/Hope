// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAIController.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "BaseAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AITargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

ABaseAIController::ABaseAIController()
	: m_groundOffset(0)
	, m_maxAttackRange(80)
{

}


void ABaseAIController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);
	SetPawn(InPawn);
	m_baseAIChar = Cast<ABaseAICharacter>(InPawn);
	m_AITargetPoints = m_baseAIChar->GetAvailableTargetPoints();

}




EPathFollowingRequestResult::Type ABaseAIController::SetVisibleTarget(APawn* InPawn)
{
	EPathFollowingRequestResult::Type result = MoveToActor(InPawn, m_maxAttackRange);
	switch (result)
	{
	case EPathFollowingRequestResult::AlreadyAtGoal:
		StopMovement();
		break;
	case EPathFollowingRequestResult::Failed:
		break; 
	case EPathFollowingRequestResult::RequestSuccessful:
		break;
	default: 
		break;
	}
	return result;
}



EPathFollowingRequestResult::Type ABaseAIController::Patrol(uint8 index)
{
	EPathFollowingRequestResult::Type result = MoveToActor(m_AITargetPoints[index]);
	return result; 
}

void ABaseAIController::SetGroundOffset(float value)
{
	m_groundOffset = value;
}
