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
		float GetCapsuleRadius();
	UFUNCTION()
		float GetCapsuleHalfHeight();

	UPROPERTY(EditAnywhere, Category = Pawn)
		class USkeletalMeshComponent* m_SkelMesh;
	UPROPERTY(EditAnywhere, Category = Pawn)
		class UShapeComponent* m_ArmCollider;
	UPROPERTY(EditAnywhere, Category = Pawn)
		class UShapeComponent* m_LegCollider;

	UPROPERTY(EditAnywhere, Category = Vision)
		float m_visionAngle;
	UPROPERTY(EditAnywhere, Category = Vision)
		float m_maxVisionRange;

	UPROPERTY(EditAnywhere, Category = Movement)
		FVector m_firstLocationOffset;
	UPROPERTY(EditAnywhere, Category = Movement)
		FVector m_secondLocationOffset;
	UPROPERTY(EditAnywhere, Category = Movement)
		float m_groundOffset;
	UPROPERTY(EditAnywhere, Category = Movement)
		float m_frontGroundOffset;
	UPROPERTY()
		class ABaseAIController* m_controller;



	UPROPERTY(EditAnywhere, Category = AI)
		class UPawnSensingComponent* m_PawnSensing; 
	UPROPERTY(EditAnywhere, Category = AI)
		class UBehaviorTree* m_behaviorTree; 



	
	
};
