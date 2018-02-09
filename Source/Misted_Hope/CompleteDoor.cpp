// Fill out your copyright notice in the Description page of Project Settings.

#include "CompleteDoor.h"
#include "Door.h"
#include "Components/BoxComponent.h"
#include "DoorChain.h"

// Sets default values
ACompleteDoor::ACompleteDoor()
	:m_isOpen(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); 
	RootComponent = m_Root; 

	m_doorLeft = CreateDefaultSubobject<ADoor>(TEXT("DoorLeft")); 
	m_doorLeft->AttachRootComponentTo(m_Root);

	m_doorRight = CreateDefaultSubobject<ADoor>(TEXT("DoorRight")); 
	m_doorRight->AttachRootComponentTo(m_Root); 

	m_TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox")); 
	m_TriggerBox->SetupAttachment(m_Root); 

	m_ChainMesh = CreateDefaultSubobject<ADoorChain>(TEXT("DoorChain")); 
	m_ChainMesh->AttachRootComponentTo(m_Root); 
}

// Called when the game starts or when spawned
void ACompleteDoor::BeginPlay()
{
	Super::BeginPlay();
	m_StartRotationL = m_doorLeft->GetActorRotation();
	m_StartRotationR = m_doorRight->GetActorRotation(); 
}

// Called every frame
void ACompleteDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (m_isOpen)
	//{
	//	m_doorLeft->OpenDoor(DeltaTime, m_StartRotationL, m_angleL, m_interSpeedL); 
	//	m_doorRight->OpenDoor(DeltaTime, m_StartRotationR, m_angleR, m_interSpeedR); 
	//	m_ChainMesh->Destroy(); 
	//}
}

