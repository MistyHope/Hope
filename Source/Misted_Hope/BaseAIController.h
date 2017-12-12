// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class MISTED_HOPE_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
	
public: 
	virtual void Possess(class APawn* InPawn) override; 
	virtual bool Move(FVector location); 
	virtual void Attack(); 


	UPROPERTY(EditAnywhere, Category = Movement)
		float m_moveDistance; 
	UPROPERTY(EditAnywhere, Category = Attacking)
		float m_maxAttackRange; 
	UPROPERTY(EditAnywhere, Category = Attacking)
		float m_attackCD; 
	
	
};
