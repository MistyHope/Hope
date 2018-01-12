// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseAICharacter.generated.h"

UCLASS()
class MISTED_HOPE_API ABaseAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void TargetIsInFOV(APawn* pawn);
	UFUNCTION()
		void TargetIsNotInFOV();
	UFUNCTION()
		float GetCapsuleRadius();
	UFUNCTION()
		float GetCapsuleHalfHeight();
	UFUNCTION()
		bool Attack();
	UFUNCTION()
		void SwitchCanAttack();
	UFUNCTION()
		void SwitchPatrolling();


	UPROPERTY(EditAnywhere, Category = Attack)
		float m_Damage; 
	UPROPERTY(EditAnywhere, Category = Attack)
		float m_PushBackForce;
	UPROPERTY(EditAnywhere, Category = Attack)
		float m_attackCD;

	UPROPERTY()
		class ABaseAIController* m_controller;
	UPROPERTY()
		class AMisted_HopeCharacter* m_char; 

	UPROPERTY(EditAnywhere, Category = AI)
		TArray<AActor*> m_AITargetPoints;
	UPROPERTY(EditAnywhere, Category = AI)
		class UPawnSensingComponent* m_PawnSensing; 
	UPROPERTY(EditAnywhere, Category = AI)
		float m_patrolDelay; 
	UPROPERTY()
		bool m_seePawn;
	UPROPERTY()
		bool m_canAttack; 
	UPROPERTY()
		bool m_isPatrolling; 
	UPROPERTY(EditAnywhere, Category = AI)
		float m_attentionDelay; 


	FORCEINLINE TArray<AActor*> GetAvailableTargetPoints() {return m_AITargetPoints;}


	FTimerHandle m_timerHandle; 
	uint32 m_instanceNum;
	uint8 m_targetIndex;
	uint32 GetCurrentInstanceNum();



};

static uint32 s_numberOfAIInstances = 0;
