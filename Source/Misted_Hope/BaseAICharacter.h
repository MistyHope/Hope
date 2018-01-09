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
		void SetIndex();

	UPROPERTY(EditAnywhere, Category = Pawn)
		class USkeletalMeshComponent* m_SkelMesh;
	UPROPERTY(EditAnywhere, Category = Pawn)
		class UShapeComponent* m_ArmCollider;
	UPROPERTY(EditAnywhere, Category = Pawn)
		class UShapeComponent* m_LegCollider;

	UPROPERTY(EditAnywhere, Category = Attack)
		float m_Damage; 
	UPROPERTY(EditAnywhere, Category = Attack)
		float m_PushBackForce;


	UPROPERTY(EditAnywhere, Category = Movement)
		float m_groundOffset;
	UPROPERTY(EditAnywhere, Category = Movement)
		float m_frontGroundOffset;
	UPROPERTY()
		class ABaseAIController* m_controller;
	UPROPERTY()
		class AMisted_HopeCharacter* m_char; 

	UPROPERTY(EditAnywhere, Category = AI)
		TArray<AActor*> m_AITargetPoints;
	UPROPERTY(EditAnywhere, Category = AI)
		class UPawnSensingComponent* m_PawnSensing; 
	UPROPERTY(EditAnywhere, Category = AI)
		class UBehaviorTree* m_behaviorTree; 
	UPROPERTY(EditAnywhere, Category = AI)
		float m_patrolDelay; 

	FORCEINLINE TArray<AActor*> GetAvailableTargetPoints() {return m_AITargetPoints;}


	FTimerHandle m_timerHandle; 
	uint32 m_instanceNum;
	uint8 m_targetIndex;
	uint32 GetCurrentInstanceNum();



};

static uint32 s_numberOfAIInstances = 0;
