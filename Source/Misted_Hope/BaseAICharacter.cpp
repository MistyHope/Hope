
// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAICharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "SmallEnemyController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"



// Sets default values
ABaseAICharacter::ABaseAICharacter()
	:m_groundOffset(30)
	, m_frontGroundOffset(30)
	,m_Damage(5)
	,m_PushBackForce(5)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	m_ArmCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Arm Collider"));
	m_ArmCollider->SetupAttachment(RootComponent);

	m_LegCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Leg Collider"));
	m_LegCollider->SetupAttachment(RootComponent);

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


}

void ABaseAICharacter::TargetIsInFOV(APawn* pawn)
{
	ABaseAIController* baseController = Cast<ABaseAIController>(GetController()); 

	if (baseController)
	{
		baseController->SetVisibleTarget(pawn);
	}

}


// Called when the game starts or when spawned
void ABaseAICharacter::BeginPlay()
{
	Super::BeginPlay();
	m_controller = Cast<ASmallEnemyController>(GetController());
	m_controller->SetForwardOffset(m_frontGroundOffset);
	m_controller->SetGroundOffset(m_groundOffset);
	m_controller->SetDamage(m_Damage);
	if (m_PawnSensing)
	{
		if (m_PawnSensing->HasLineOfSightTo(GetWorld()->GetFirstPlayerController()->GetCharacter()))
		{
			m_PawnSensing->OnSeePawn.AddDynamic(this, &ABaseAICharacter::TargetIsInFOV);
			m_SeePawn = true; 
		}
		else
		{
			m_SeePawn = false; 
		}
	}
}

// Called every frame
void ABaseAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
