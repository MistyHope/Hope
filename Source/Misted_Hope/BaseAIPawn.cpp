// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAIPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABaseAIPawn::ABaseAIPawn()
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
	
}

// Called every frame
void ABaseAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
