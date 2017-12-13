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
	virtual bool Move(FVector location); 
	virtual void Attack(); 
	void Tick(float DeltaTime) override; 

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
		class ABaseAIPawn* baseAIPawn; 
	UPROPERTY()
		float m_forwardGroundOffset; 
	UPROPERTY()
		float m_groundOffset; 


protected: 
	void BeginPlay() override; 
};
