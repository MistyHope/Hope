// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBTTask.h"
#include "BaseAIController.h"
#include "AITargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBaseBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseAIController* baseController = Cast<ABaseAIController>(OwnerComp.GetAIOwner()); 

	if (baseController)
	{

		UBlackboardComponent* blackBoardComp = baseController->GetBlackBoardComp();

		SetMovingKey(blackBoardComp, baseController);

		if (blackBoardComp->GetValueAsObject("Target"))
			return EBTNodeResult::Failed;


		blackBoardComp->GetValueAsObject("LocationToGo");
		return EBTNodeResult::Succeeded;
		

	}
	else
		return EBTNodeResult::Failed; 
}

void UBaseBTTask::SetMovingKey(UBlackboardComponent* blackBoardComp, ABaseAIController* baseAiController)
{
	TArray<AActor*> availableTargetPoints = baseAiController->GetAvailableTargetPoints();

	int32 Index = 0;
	AAITargetPoint* currentPoint = Cast<AAITargetPoint>(blackBoardComp->GetValueAsObject("LocationToGo"));

	AAITargetPoint* nextTargetPoint = nullptr;

	do
	{
		if (Index > availableTargetPoints.Num())
			Index = 0;
		nextTargetPoint = Cast<AAITargetPoint>(availableTargetPoints[Index]);
		Index++;
		baseAiController->MoveToActor(nextTargetPoint);
	} while (currentPoint == nextTargetPoint);


	blackBoardComp->SetValueAsObject("LocationToGo", nextTargetPoint);

}

