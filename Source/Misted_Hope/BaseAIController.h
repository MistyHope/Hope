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
		void SetGroundOffset(float value); 

	UPROPERTY(EditAnywhere, Category = Movement)
		float m_moveDistance; 
	UPROPERTY(EditAnywhere, Category = Attacking)
		float m_maxAttackRange; 
	UPROPERTY(EditAnywhere, Category = Attacking)
		float m_attackCD; 
	UPROPERTY(EditAnywhere, Category = Attacking)
		float m_Damage;


	UPROPERTY()
		class ABaseAICharacter* m_baseAIChar; 
	UPROPERTY()
		float m_groundOffset; 
	UPROPERTY(EditAnywhere, Category = AI)
		TArray<AActor*> m_AITargetPoints; 
	UPROPERTY(EditDefaultsOnly, Category = AI)
		FName m_LocationToGoKey;
	UPROPERTY(EditDefaultsOnly, Category = AI)
		FName m_TargetKey; 


	UFUNCTION()
		void SetVisibleTarget(APawn* InPawn); 
	UFUNCTION()
		bool Patrol(uint8 index);
	UFUNCTION()
		TArray<AActor*> GetAvailableTargetPoints() { return m_AITargetPoints; }
protected: 
};
