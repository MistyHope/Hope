// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAIPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "SmallEnemyController.h"

// Sets default values
ABaseAIPawn::ABaseAIPawn()
	:m_groundOffset(30)
	, m_frontGroundOffset(30)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	m_RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root")); 
	RootComponent = m_RootCapsule; 

	m_SkelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh")); 
	m_SkelMesh->SetupAttachment(RootComponent); 

	m_ArmCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Arm Collider")); 
	m_ArmCollider->SetupAttachment(RootComponent);

	m_LegCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Leg Collider")); 
	m_LegCollider->SetupAttachment(RootComponent); 

}

// Called when the game starts or when spawned
void ABaseAIPawn::BeginPlay()
{
	Super::BeginPlay();
	m_controller = Cast<ASmallEnemyController>(GetController());
	m_controller->SetForwardOffset(m_frontGroundOffset); 
	m_controller->SetGroundOffset(m_groundOffset);
}

// Called every frame
void ABaseAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_controller)
		MovePawn(GetActorLocation() + m_firstLocationOffset, GetActorLocation() + m_secondLocationOffset);
}

// Called to bind functionality to input
void ABaseAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


bool ABaseAIPawn::TargetIsInFOV(AActor* otherActor)
{
	return false; 
}

bool ABaseAIPawn::MovePawn(FVector vec1, FVector vec2)
{
	if (m_controller->Move(GetActorLocation() + m_firstLocationOffset))
		m_controller->Move(GetActorLocation() + m_secondLocationOffset);


	return false; 

}



float ABaseAIPawn::GetCapsuleRadius()
{
	return m_RootCapsule->GetScaledCapsuleRadius(); 
}

float ABaseAIPawn::GetCapsuleHalfHeight()
{
	return m_RootCapsule->GetScaledCapsuleHalfHeight();
}