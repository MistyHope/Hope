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

	ABaseAIController();

	virtual void Possess(class APawn* InPawn) override; 
	virtual void Attack(); 

	UFUNCTION()
		void SetForwardOffset(float value); 
	UFUNCTION()
		void SetGroundOffset(float value); 

	UPROPERTY(EditAnywhere, Category = Movement)
		float m_moveDistance; 
	UPROPERTY(EditAnywhere, Category = Attacking)
		float m_maxAttackRange; 
	UPROPERTY(EditAnywhere, Category = Attacking)
		float m_attackCD; 
	UPROPERTY()
		class ABaseAICharacter* m_baseAIChar; 
	UPROPERTY()
		float m_forwardGroundOffset; 
	UPROPERTY()
		float m_groundOffset; 
	UPROPERTY()
		class UBehaviorTreeComponent*  m_behaviorTree; 
	UPROPERTY()
		class UBlackboardComponent* m_blackBoardComp; 
	UPROPERTY()
		TArray<AActor*> m_AITargetPoints; 
	UPROPERTY(EditDefaultsOnly, Category = AI)
		FName m_LocationToGoKey;
	UPROPERTY(EditDefaultsOnly, Category = AI)
		FName m_TargetKey; 

	UFUNCTION()
		void SetVisibleTarget(APawn* InPawn); 
	UFUNCTION()
		UBlackboardComponent* GetBlackBoardComp() const { return m_blackBoardComp; }
	UFUNCTION()
		TArray<AActor*> GetAvailableTargetPoints() { return m_AITargetPoints; }


protected: 
};
