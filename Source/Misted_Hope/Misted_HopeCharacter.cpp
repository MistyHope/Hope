// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Misted_HopeCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
//#include "EngineGlobals.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

#include "PushableBox.h"
#include "Collectables.h"


DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

//////////////////////////////////////////////////////////////////////////
// AMisted_HopeCharacter

AMisted_HopeCharacter::AMisted_HopeCharacter()
	: m_bIsRunning(false)
	, m_bIsPushing(false)
	, m_RingOrigin(0, 0, 0)
	, m_bLookRight(false)
	,m_CharacterHeight(60)
	,m_CharacterWidth(30)
	,m_iForceValue(11000)
	,m_LastGroundedPos(0,0,0)
	, m_bGrounded(false)
{
	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(m_CharacterHeight);
	GetCapsuleComponent()->SetCapsuleRadius(m_CharacterWidth);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMisted_HopeCharacter::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMisted_HopeCharacter::OnOverlapEnd);

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->RelativeRotation = FRotator(0.0f, -90.0f, 0.0f);


	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Perspective;
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	CameraBoom->bAbsoluteRotation = true;
	SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->GetNavAgentProperties()->bCanCrouch = true; 


	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;

}

//////////////////////////////////////////////////////////////////////////
// Animation

void AMisted_HopeCharacter::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

	// Are we moving or standing still?
	UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? RunningAnimation : IdleAnimation;
	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}

void AMisted_HopeCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateCharacter();
}


//////////////////////////////////////////////////////////////////////////
// Input

void AMisted_HopeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMisted_HopeCharacter::MoveRight);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMisted_HopeCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AMisted_HopeCharacter::UnRun);
	PlayerInputComponent->BindAction("PushObjects", IE_Pressed, this, &AMisted_HopeCharacter::PushObjects);
	PlayerInputComponent->BindAction("PushObjects", IE_Released, this, &AMisted_HopeCharacter::UnPushObjects);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AMisted_HopeCharacter::Interaction);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMisted_HopeCharacter::ToggleCrouch); 
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMisted_HopeCharacter::ToggleCrouch);

}

void AMisted_HopeCharacter::MoveRight(float Value)
{

	if (Value > 0)
		m_bLookRight = true;
	else
		m_bLookRight = false; 
	
	FHitResult RV_Hit(ForceInit);
	bool hitResult;
	if (m_bLookRight)
		hitResult = GetWorld()->LineTraceSingleByObjectType(RV_Hit, GetActorLocation(), GetActorLocation() + FVector(30,0,0), ECC_WorldStatic);
	else
		hitResult = GetWorld()->LineTraceSingleByObjectType(RV_Hit, GetActorLocation(), GetActorLocation() - FVector(30, 0, 0), ECC_WorldStatic);



	if (!hitResult && !m_bIsPushing)
	{
		AddMovementInput(FVector(1,0,0), Value);
	}
	else if (m_bIsPushing)
	{
		AddMovementInput(FVector(.2,0,0), Value);

		m_NearActor->GetRootPrimitiveComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		m_NearActor->GetRootPrimitiveComponent()->SetSimulatePhysics(true);
		m_NearActor->SetActorLocation(FVector(GetActorLocation().X + m_distToBox, m_NearActor->GetActorLocation().Y, m_NearActor->GetActorLocation().Z));
	}		

}

void AMisted_HopeCharacter::TrampolineJump(float jumpMultiplicator)
{
	Jump();
}

void AMisted_HopeCharacter::ToggleCrouch()
{
	if (CanCrouch())
	{
		Crouch();
		GetCapsuleComponent()->SetCapsuleHalfHeight(CrouchedEyeHeight);
	}
	else
	{
		UnCrouch();
		GetCapsuleComponent()->SetCapsuleHalfHeight(m_CharacterHeight);
	}
}


void AMisted_HopeCharacter::Run()
{
	//TODO: Add Animation 
	m_bIsRunning = true;
}

void AMisted_HopeCharacter::UnRun()
{
	//TODO: Add Animation 
	m_bIsRunning = false;
}

void AMisted_HopeCharacter::Interaction()
{
	m_bInteract = true;
}

void AMisted_HopeCharacter::PushObjects()
{
	if (!m_bIsPushing && m_bNearBox)
	{
		m_distToBox = m_NearActor->GetActorLocation().X - GetActorLocation().X;
		m_bIsPushing = true;
	}
}

void AMisted_HopeCharacter::UnPushObjects()
{
	if(m_bIsPushing)
		m_bIsPushing = false;
}

void AMisted_HopeCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->GetFName() == TEXT("PushableBox"))
	{
		m_bNearBox = true; 
		m_NearActor = OtherActor; 
	}
	else if (OtherActor->GetClass()->GetFName() == TEXT("Collectables"))
	{
		ACollectables* collectable = (ACollectables*)OtherActor->GetClass();
		collectable->Collect();
	}
	
}

void AMisted_HopeCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	m_bNearBox = false;
	m_NearActor = nullptr; 
	m_bIsPushing = false; 
}

void AMisted_HopeCharacter::UpdateCharacter()
{
	

	// Set the rotation so that the character faces his direction of travel.
	// Update animation to match the motion
	UpdateAnimation();

	if (!m_bIsPushing && m_NearActor != nullptr)
	{
		m_NearActor->GetRootPrimitiveComponent()->SetSimulatePhysics(false);
	}



	// Now setup the rotation of the controller based on the direction we are travelling
	const FVector PlayerVelocity = GetVelocity();
	float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}
