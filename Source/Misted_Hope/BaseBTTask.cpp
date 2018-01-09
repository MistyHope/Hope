// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBTTask.h"
#include "BaseAIController.h"
#include "AITargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseAICharacter.h"

EBTNodeResult::Type UBaseBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//ABaseAIController* baseController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());

	//if (baseController)
	//{

	//	UBlackboardComponent* blackBoardComp = baseController->GetBlackBoardComp();

	//	return SetMovingKey(blackBoardComp, baseController);
	//}
	//else
		return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBaseBTTask::SetMovingKey(UBlackboardComponent* blackBoardComp, ABaseAIController* baseAiController)
{
	/*TArray<AActor*> availableTargetPoints = baseAiController->GetAvailableTargetPoints();

	int32 Index = 0;
	AAITargetPoint* currentPoint = Cast<AAITargetPoint>(blackBoardComp->GetValueAsObject("LocationToGo"));

	AAITargetPoint* nextTargetPoint = nullptr;

	ABaseAICharacter* baseChar = Cast<ABaseAICharacter>(baseAiController->GetCharacter());
	uint32 charInstance = baseChar->GetCurrentInstanceNum();
	EPathFollowingRequestResult::Type resultType;
	if (baseChar)
	{
		do
		{
			if (Index >= availableTargetPoints.Num())
				Index = 0;
			nextTargetPoint = Cast<AAITargetPoint>(availableTargetPoints[Index]);
			uint32 nextTargetInstance = nextTargetPoint->GetCurrentChar()->GetCurrentInstanceNum();
			if (nextTargetInstance == charInstance)
			{
				Index++;
				if (blackBoardComp->GetValueAsObject("Target"))
					return EBTNodeResult::Failed;
				resultType = baseAiController->MoveToActor(nextTargetPoint);
				
			}
			else
				return EBTNodeResult::Failed;
		} while (currentPoint == nextTargetPoint);


			blackBoardComp->SetValueAsObject("LocationToGo", nextTargetPoint);
			return EBTNodeResult::Succeeded;
	}
	else
		return EBTNodeResult::Failed;*/
	return EBTNodeResult::Failed; 
}

