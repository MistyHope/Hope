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
	, m_TargetKey("Target")
	, m_LocationToGoKey("LocationToGo")
{

}


void ABaseAIController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);
	SetPawn(InPawn);
	m_baseAIChar = Cast<ABaseAICharacter>(InPawn);
	m_AITargetPoints = m_baseAIChar->GetAvailableTargetPoints();

}




void ABaseAIController::SetVisibleTarget(APawn* InPawn)
{
	MoveToActor(InPawn);
}

bool ABaseAIController::Patrol(uint8 index)
{
	EPathFollowingRequestResult::Type result = MoveToActor(m_AITargetPoints[index]);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *m_AITargetPoints[index]->GetFName().ToString())
	switch (result)
	{
	case EPathFollowingRequestResult::AlreadyAtGoal:
		return true; 
			break; 
	default: 
		return false; 
			break; 
	}
	return false; 
}


void ABaseAIController::Attack()
{

}

void ABaseAIController::SetGroundOffset(float value)
{
	m_groundOffset = value;
}
