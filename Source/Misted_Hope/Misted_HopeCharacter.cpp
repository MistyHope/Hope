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
#include "Components/Widget.h"
#include "PushableBox.h"
#include "Collectables.h"
#include "CompleteDoor.h"
#include "CheckpointManager.h"


DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

//////////////////////////////////////////////////////////////////////////
// AMisted_HopeCharacter

AMisted_HopeCharacter::AMisted_HopeCharacter()
	: m_bIsPushing(false)
	, m_bLookRight(false)
	, m_CharacterHeight(60)
	, m_CharacterWidth(30)
	, m_LastGroundedPos(0, 0, 0)
	, m_bGrounded(false)
	, m_InAirMovementpower(1.23)
	, m_PlayerHope(3)
	, m_NormalHerbValue(5)
	, m_SpecialHerbValue(5)
	, m_isVisible(true)
	, m_MaxPlayerHope(3)
	, m_getSpecialHerb(false)
	,m_cameraBoomY(0)
	,m_hasKey(false)
	,m_nearDoor(false)
	,m_cameraXOffset(50)
	,m_isDead(false)
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

	m_CPManager = CreateDefaultSubobject<ACheckpointManager>(TEXT("CPManager")); 
}

void AMisted_HopeCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateCharacter();
	if (m_cameraBoomY == 0)
		m_cameraBoomY = CameraBoom->GetComponentLocation().Y;
	else
		CameraBoom->SetWorldLocation(FVector(CameraBoom->GetComponentLocation().X, m_cameraBoomY, CameraBoom->GetComponentLocation().Z));

	if (m_bLookRight)
		CameraBoom->SocketOffset = UKismetMathLibrary::VInterpTo(FVector(0, 0, 13), FVector(0, m_cameraXOffset,13), DeltaSeconds, 1);
	else
		CameraBoom->SocketOffset = UKismetMathLibrary::VInterpTo(FVector(0, 0, 13), FVector(0, -m_cameraXOffset,13 ), DeltaSeconds, 1);
}


//////////////////////////////////////////////////////////////////////////
// Input

void AMisted_HopeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{

	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMisted_HopeCharacter::MoveRight);
	PlayerInputComponent->BindAction("PushObjects", IE_Pressed, this, &AMisted_HopeCharacter::PushObjects);
	PlayerInputComponent->BindAction("PushObjects", IE_Released, this, &AMisted_HopeCharacter::UnPushObjects);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AMisted_HopeCharacter::Interaction);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMisted_HopeCharacter::ToggleCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMisted_HopeCharacter::ToggleCrouch);
	PlayerInputComponent->BindAction("Respawn", IE_Pressed, this, &AMisted_HopeCharacter::ResetPlayerAfterDead);
}

void AMisted_HopeCharacter::MoveRight(float Value)
{
	if (!m_isDead)
	{
		if (Value > 0)
			m_bLookRight = true;
		else
			m_bLookRight = false;




		FHitResult RV_Hit(ForceInit);
		bool hitResult;
		if (m_bLookRight)
			hitResult = GetWorld()->LineTraceSingleByObjectType(RV_Hit, GetActorLocation(), GetActorLocation() + FVector(30, 0, 0), ECC_WorldStatic);
		else
			hitResult = GetWorld()->LineTraceSingleByObjectType(RV_Hit, GetActorLocation(), GetActorLocation() - FVector(30, 0, 0), ECC_WorldStatic);

		if (!hitResult && !m_bIsPushing)
		{
			AddMovementInput(FVector(1, 0, 0), Value);
		}
		else if (m_bIsPushing)
		{
			AddMovementInput(FVector(.2, 0, 0), Value);

			UPrimitiveComponent* nearActorPrim = Cast<UPrimitiveComponent>(m_NearActor->GetRootComponent());

			nearActorPrim->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			nearActorPrim->SetSimulatePhysics(true);
			if (!GetWorld()->LineTraceSingleByObjectType(RV_Hit, m_NearActor->GetActorLocation(), m_NearActor->GetActorLocation() + FVector(50 * Value, 0, 0), ECC_WorldStatic))
				m_NearActor->SetActorLocation(FVector(GetActorLocation().X + m_distToBox, m_NearActor->GetActorLocation().Y, m_NearActor->GetActorLocation().Z));
		}
	}
}

void AMisted_HopeCharacter::TrampolineJump(float jumpMultiplicator)
{
	this->LaunchCharacter(FVector(0, 0, jumpMultiplicator), false, true);
}

float AMisted_HopeCharacter::GetPlayerHope()
{
	return m_PlayerHope;
}

void AMisted_HopeCharacter::ToggleCrouch()
{
	FHitResult RV_Hit(ForceInit);
	if (CanCrouch() && !m_bIsPushing)
	{
		Crouch();
		GetCapsuleComponent()->SetCapsuleHalfHeight(CrouchedEyeHeight);
	}
	else if (!GetWorld()->LineTraceSingleByObjectType(RV_Hit, GetActorLocation(), GetActorLocation() + FVector(0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + 15, 0), ECC_WorldStatic))
	{
		UnCrouch();
		GetCapsuleComponent()->SetCapsuleHalfHeight(m_CharacterHeight);
	}
}


void AMisted_HopeCharacter::Interaction()
{
	if (m_nearDoor && m_getSpecialHerb)
		m_NearDoor->m_isOpen = true;
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
	if (m_bIsPushing)
		m_bIsPushing = false;
}



void AMisted_HopeCharacter::Collect(ECollectables collectable)
{
	switch (collectable)
	{
	case NormalHerb:
		if(m_PlayerHope<m_MaxPlayerHope)
			m_PlayerHope += m_NormalHerbValue;
		break;
	case SpecialHerb:
		m_getSpecialHerb = true;
		if (m_PlayerHope<m_MaxPlayerHope)
			m_PlayerHope += m_SpecialHerbValue ;
		break;
	}
	UE_LOG(LogTemp, Warning, TEXT("%i"), m_PlayerHope);

}

void AMisted_HopeCharacter::Hurt(float Value)
{
	m_PlayerHope -= Value;
	if (m_PlayerHope <= 0)
		m_isDead = true; 
	UE_LOG(LogTemp, Warning, TEXT("%i"), m_PlayerHope);
}


void AMisted_HopeCharacter::PushBack(FVector vec)
{
	this->LaunchCharacter(vec, true, false);
}


void AMisted_HopeCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APushableBox* box = Cast<APushableBox>(OtherActor);
	ACompleteDoor* door = Cast<ACompleteDoor>(OtherActor);
	if (box)
	{
		m_bNearBox = true;
		m_NearActor = OtherActor;
	}
	if (door)
	{
		m_NearDoor = door; 
		m_nearDoor = true; 
	}
}

void AMisted_HopeCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APushableBox* box = Cast<APushableBox>(OtherActor);
	ACompleteDoor* door = Cast<ACompleteDoor>(OtherActor);
	if (box)
	{
		UPrimitiveComponent* nearActorPrim = Cast<UPrimitiveComponent>(m_NearActor->GetRootComponent());
		nearActorPrim->SetSimulatePhysics(false);
		m_bNearBox = false;
		m_NearActor = nullptr;
		m_bIsPushing = false;
	}
	if (door)
	{
		m_nearDoor = false;
		m_NearDoor = nullptr;

	}
}

void AMisted_HopeCharacter::ResetPlayerAfterDead()
{
	m_isDead = false; 
	m_CPManager->SetCharacterToCP();
}

void AMisted_HopeCharacter::UpdateCharacter()
{

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
