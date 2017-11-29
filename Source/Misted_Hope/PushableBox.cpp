// Fill out your copyright notice in the Description page of Project Settings.

#include "PushableBox.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Misted_HopeCharacter.h"

// Sets default values
APushableBox::APushableBox()

{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); 
	m_Mesh->SetupAttachment(RootComponent); 
	m_Mesh->BodyInstance.bLockXRotation = true; 
	m_Mesh->BodyInstance.bLockYRotation = true; 
	m_Mesh->BodyInstance.bLockZRotation = true; 

	m_TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerComponent")); 
	m_TriggerBox->SetupAttachment(RootComponent); 
 
}

// Called when the game starts or when spawned
void APushableBox::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APushableBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Changes the RootState of the object to provide the object to get moved from the character without getting grabbed
}