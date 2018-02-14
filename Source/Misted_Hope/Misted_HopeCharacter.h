// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EnumAndStructHolder.h"
#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Misted_HopeCharacter.generated.h"

class UTextRenderComponent;

/**
 * This class is the default character for Misted_Hope, and it is responsible for all
 * physical interaction between the player and the world.
 *
 * The capsule component (inherited from ACharacter) handles collision with the world
 * The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
 * The Sprite component (inherited from APaperCharacter) handles the visuals
 */



UCLASS(config=Game)
class AMisted_HopeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UTextRenderComponent* TextComponent;
	virtual void Tick(float DeltaSeconds) override;
protected:


public: 
	UPROPERTY(EditAnywhere, Category = Movement)
		float m_InAirMovementpower; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		int m_PlayerHope;
	UPROPERTY(BlueprintReadOnly)
		bool m_getSpecialHerb; 
	UPROPERTY(EditAnywhere, Category = Character)
		float m_MaxPlayerHope; 
	UPROPERTY(EditAnywhere, Category = Character)
		float m_NormalHerbValue; 
	UPROPERTY(EditAnywhere, Category = Character)
		float m_SpecialHerbValue; 
	UFUNCTION(BlueprintCallable)
		float GetPlayerHope(); 
	UPROPERTY(BlueprintReadOnly)
		bool m_bIsPushing; 
	UPROPERTY(EditAnywhere, Category = Character)
		bool m_cantWalkRight;
	UPROPERTY(EditAnywhere, Category = Character)
		bool m_cantWalkLeft;
	bool m_bLookRight; 
	UPROPERTY(BlueprintReadOnly)
		bool m_gotBottle; 
	UPROPERTY()
		bool m_nearDoor; 
	UPROPERTY(EditAnywhere,  Category = CharacterBasics)
		float m_CharacterHeight;
	UPROPERTY(EditAnywhere, Category = CharacterBasics)
		float m_CharacterWidth; 
	UPROPERTY()
		bool m_hasKey; 
	UPROPERTY()
		float m_cameraBoomY;
	UPROPERTY(EditAnywhere, Category = Camera)
		float m_cameraXOffset; 
	UPROPERTY(EditAnywhere, Category = Character)
		class ACheckpointManager* m_CPManager; 
	UPROPERTY(BlueprintReadOnly)
		bool m_isDead;
	class ACompleteDoor* m_NearDoor;  
	UPROPERTY(BlueprintReadOnly)
		float m_PushValue; 
	UPROPERTY()
		bool m_LeftPush; 
	UPROPERTY()
		bool m_RightPush; 
	bool m_bNearBox; 
	
	bool m_bGrounded; 

	UPROPERTY()
		bool m_isVisible; 

	float m_distToBox; 

	FVector m_LastGroundedPos; 

public: 

	/** Called for side to side input */
	void MoveRight(float Value);

	void ToggleCrouch();		

	void Interaction(); 

	void PushObjects();

	void UnPushObjects();

	void UpdateCharacter();
	UFUNCTION()
		void Jump();
	UFUNCTION()
		void PushBack(FVector vec);
	UFUNCTION()
		void TrampolineJump(float jumpMultiplicator); 
	UFUNCTION()
		void Collect(ECollectables collectable); 
	UFUNCTION()
		void Hurt(float value);
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void SetPlayerHope(int hope) { m_PlayerHope = hope; }
	UFUNCTION()
		void ResetPlayerAfterDead();
	UFUNCTION(BlueprintCallable) 
		bool GetStatus() { return m_isDead; }


	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	AMisted_HopeCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
