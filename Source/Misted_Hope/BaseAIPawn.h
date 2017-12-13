// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseAIPawn.generated.h"

UCLASS(abstract)
class MISTED_HOPE_API ABaseAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseAIPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		bool TargetIsInFOV(AActor* otherActor); 
	UFUNCTION()
		float GetCapsuleRadius(); 
	UFUNCTION()
		float GetCapsuleHalfHeight();
	UFUNCTION()
		bool MovePawn(FVector vec1, FVector vec2); 


	UPROPERTY(EditAnywhere, Category = Pawn)
		class UCapsuleComponent* m_RootCapsule; 
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

};
