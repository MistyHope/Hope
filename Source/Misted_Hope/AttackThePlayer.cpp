// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackThePlayer.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Misted_HopeCharacter.h"
#include "BaseAIController.h"
#include "BaseAICharacter.h"


EBTNodeResult::Type UAttackThePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
	UBlackboardComponent* blackBoard = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	AMisted_HopeCharacter* Character = Cast<AMisted_HopeCharacter>(blackBoard->GetValueAsObject("Target"));
	ABaseAICharacter* OwnerAI = Cast<ABaseAICharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	Character->Hurt(OwnerAI->m_Damage);
	if (OwnerAI->GetActorLocation().X < Character->GetActorLocation().X)
		Character->PushBack(FVector(1, 0, 0)*OwnerAI->m_PushBackForce);
	else
		Character->PushBack(FVector(-1, 0, 0)*OwnerAI->m_PushBackForce);
	return EBTNodeResult::Succeeded;
}


