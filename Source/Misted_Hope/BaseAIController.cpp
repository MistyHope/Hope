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

ABaseAIController::ABaseAIController()
	:m_forwardGroundOffset(0)
	, m_groundOffset(0)
	, m_TargetKey("Target")
	, m_LocationToGoKey("LocationToGo")
{
	m_behaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));

	m_blackBoardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp")); 


}


void ABaseAIController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);
	SetPawn(InPawn);
	m_baseAIChar = Cast<ABaseAICharacter>(InPawn);



	if (m_baseAIChar)
	{
		if (m_baseAIChar->m_behaviorTree->BlackboardAsset)
		{
			m_blackBoardComp->InitializeBlackboard(*(m_baseAIChar->m_behaviorTree->BlackboardAsset));
		}
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAITargetPoint::StaticClass(), m_AITargetPoints); 

		m_behaviorTree->StartTree(*m_baseAIChar->m_behaviorTree);
	}



}


void ABaseAIController::SetDamage(float Value)
{
	m_Damage = Value; 
}

void ABaseAIController::SetVisibleTarget(APawn* InPawn)
{
	if (m_blackBoardComp)
	{
		m_blackBoardComp->SetValueAsObject(m_TargetKey, InPawn);
	}
}


void ABaseAIController::Attack()
{

}

void ABaseAIController::SetGroundOffset(float value)
{
	m_groundOffset = value;
}

void ABaseAIController::SetForwardOffset(float value)
{
	m_forwardGroundOffset = value;
}