// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BaseBTTask.generated.h"



UENUM(BlueprintType)
enum EBaseEnemyStates
{
	Moving, 
	Attacking
};
/**
 * 
 */
UCLASS()
class MISTED_HOPE_API UBaseBTTask : public UBTTaskNode
{
	GENERATED_BODY()
	

public: 
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; 


	EBTNodeResult::Type SetMovingKey(class UBlackboardComponent* blackBoardComp, class ABaseAIController* baseAiController);




	
	
	
};
