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


DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

//////////////////////////////////////////////////////////////////////////
// AMisted_HopeCharacter

AMisted_HopeCharacter::AMisted_HopeCharacter()
	: m_bIsRunning(false)
	, m_bIsPushing(false)
	, m_RingOrigin(0, 0, 0)
	, m_bLookRight(false)
{
	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);
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
	//SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;
	//GetCharacterMovement()->bOrientRotationToMovement = false;

	// Configure character movement
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 800;
	GetCharacterMovement()->GroundFriction = 3.0f;
	m_fMaxSpeed = GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;


	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

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
	if (!m_bLookRight)
		GetSprite()->SetRelativeRotation(FRotator(0, 180, 0));
	else
		GetSprite()->SetRelativeRotation(FRotator(0, 0, 0));

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
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMisted_HopeCharacter::Crouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMisted_HopeCharacter::UnCrouch);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMisted_HopeCharacter::MoveRight);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMisted_HopeCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AMisted_HopeCharacter::UnRun);
	PlayerInputComponent->BindAction("PushObjects", IE_Pressed, this, &AMisted_HopeCharacter::PushObjects);
	PlayerInputComponent->BindAction("PushObjects", IE_Released, this, &AMisted_HopeCharacter::UnPushObjects);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AMisted_HopeCharacter::Interaction);
}

void AMisted_HopeCharacter::MoveRight(float Value)
{
	/*UpdateChar();*/
	// Apply the input to the character motion


	float dist = (m_RingOrigin - GetActorLocation()).Size(); 

	if (Value > 0)
	{
		if (dist < m_RingOrigin.Y)
		{
			AddActorWorldRotation(FRotator(0, -3.0f, 0));

		}
		else if (dist > m_RingOrigin.Y)
		{
			AddActorWorldRotation(FRotator(0, 3.0f, 0));
		}
	}
	else if (Value < 0)
	{
		if (dist < m_RingOrigin.Y)
		{
			AddActorWorldRotation(FRotator(0, 3.0f, 0));
		}
		else if (dist > m_RingOrigin.Y)
		{
			AddActorWorldRotation(FRotator(0, -3.0f, 0)); 
		}
	}

	if (Value < 0)
		m_bLookRight = false;
	else if (Value > 0)
		m_bLookRight = true; 
	FHitResult RV_Hit(ForceInit);
	bool hitResult;
	if (m_bLookRight)
		hitResult = GetWorld()->LineTraceSingleByObjectType(RV_Hit, GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * 70), ECC_WorldStatic);
	else
		hitResult = GetWorld()->LineTraceSingleByObjectType(RV_Hit, GetActorLocation(), GetActorLocation() - (GetActorForwardVector() * 70), ECC_WorldStatic);

	if (!hitResult)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
		
}

void AMisted_HopeCharacter::Crouch()
{
	//TODO: Add animation
	//GetCapsuleComponent()->SetCapsuleHalfHeight(GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()/2);
}

void AMisted_HopeCharacter::UnCrouch()
{
	//TODO: Add Animation
	//GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);

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
	if(m_bNearBox && !m_bIsPushing)
		m_bIsPushing = true;
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
	}
	

}

void AMisted_HopeCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetClass()->GetFName() == TEXT("PushableBox"))
	{
		if (m_bIsPushing)
		{
			m_bIsPushing = false; 
		}
	}
	m_bNearBox = false; 
}

void AMisted_HopeCharacter::UpdateCharacter()
{
	// Update animation to match the motion
	UpdateAnimation();
	//SideViewCameraComponent

	FHitResult RV_Hit(ForceInit);


	bool hitResult = GetWorld()->LineTraceSingleByObjectType(RV_Hit, GetActorLocation(), GetActorLocation() - FVector(0, 0, 500), ECC_WorldStatic);
	if (hitResult && m_RingOrigin.IsZero())
	{
		FVector actorLoc;
		actorLoc = RV_Hit.GetActor()->GetActorLocation();
		bool originResult = GetWorld()->LineTraceSingleByObjectType(RV_Hit, actorLoc, actorLoc + FVector(0, 9999, 0), ECC_WorldStatic);
		if (originResult)
		{
			float dist = RV_Hit.Distance;
			m_RingOrigin = FVector(actorLoc.X, actorLoc.Y + dist / 2, actorLoc.Z);
			m_RingOrigin = FVector(m_RingOrigin.X, m_RingOrigin.Y + 40, m_RingOrigin.Z);
		}
	}
	

	FRotator actorRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), m_RingOrigin);

	FVector cameraLookAtLeft = GetActorLocation() - (-GetActorRightVector());

	FRotator cameraRotLeft = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), cameraLookAtLeft);

	CameraBoom->SetWorldRotation(cameraRotLeft); 


	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		Controller->SetControlRotation(actorRot - FRotator(0, 90, 0)); 
		
	}
}
