
// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAICharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "SmallEnemyController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Misted_HopeCharacter.h"
#include "Engine/Engine.h"



// Sets default values
ABaseAICharacter::ABaseAICharacter()
	:m_Damage(5)
	,m_PushBackForce(5)
	, m_targetIndex(0)
	,m_patrolDelay(5)
	,m_seePawn(false)
	,m_attackCD(3)
	, m_canAttack(true)

{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->GetNavAgentProperties()->bCanCrouch = true;


	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	m_PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Perception")); 

	m_PawnSensing->SetPeripheralVisionAngle(90); 
	m_PawnSensing->bOnlySensePlayers = true;

	s_numberOfAIInstances++;
}


uint32 ABaseAICharacter::GetCurrentInstanceNum()
{
	return m_instanceNum;
}


void ABaseAICharacter::TargetIsInFOV(APawn* pawn)
{
	ABaseAIController* baseController = Cast<ABaseAIController>(GetController()); 
	m_seePawn = true; 
	if (baseController)
	{
		if (m_PawnSensing->HasLineOfSightTo(m_char) && m_char->m_isVisible)
		{
			EPathFollowingRequestResult::Type result = baseController->SetVisibleTarget(pawn);
			switch (result)
			{
			case EPathFollowingRequestResult::AlreadyAtGoal:
				if (m_canAttack)
				{
					if (Attack())
					{
						m_canAttack = false;
						GetWorldTimerManager().SetTimer(m_timerHandle, this, &ABaseAICharacter::SwitchCanAttack, m_attackCD, true);
					}
				}
				break;
			default:
				break;
			}
		}
		else
			m_seePawn = false; 
	}
	else 
		m_seePawn = false; 
	if(m_seePawn)
		GetWorldTimerManager().SetTimer(m_timerHandle, this, &ABaseAICharacter::SwitchCanSee, m_patrolDelay, true);
}

void ABaseAICharacter::SwitchCanAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("Switch the Attack"));

	m_canAttack = !m_canAttack;
}

void ABaseAICharacter::SwitchCanSee()
{
	UE_LOG(LogTemp, Warning, TEXT("Switch the SeePawn"));

	m_seePawn = !m_seePawn; 
}


bool ABaseAICharacter::Attack()
{
	m_char->Hurt(m_Damage); 
	m_char->PushBack(GetActorForwardVector()*m_PushBackForce);
	return true; 
}

// Called when the game starts or when spawned
void ABaseAICharacter::BeginPlay()
{
	Super::BeginPlay();
	m_char = Cast<AMisted_HopeCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	m_controller = Cast<ASmallEnemyController>(GetController());
	if (m_PawnSensing)
	{
		m_PawnSensing->OnSeePawn.AddDynamic(this, &ABaseAICharacter::TargetIsInFOV);
	}
}

void ABaseAICharacter::TargetIsNotInFOV()
{
	ABaseAIController* baseController = Cast<ABaseAIController>(GetController());
	if (baseController)
	{
		if (baseController->Patrol(m_targetIndex))
		{
			if (m_targetIndex < m_AITargetPoints.Num() - 1)
				m_targetIndex++;
			else
				m_targetIndex = 0;
		
		}
	}
}

// Called every frame
void ABaseAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((!m_seePawn || m_seePawn && !m_char->m_isVisible))
		TargetIsNotInFOV();
	else if(m_canAttack)
		TargetIsInFOV(m_char);
}

// Called to bind functionality to input
void ABaseAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


float ABaseAICharacter::GetCapsuleHalfHeight()
{
	return  GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
}


float ABaseAICharacter::GetCapsuleRadius()
{
	return GetCapsuleComponent()->GetScaledCapsuleRadius();
}


