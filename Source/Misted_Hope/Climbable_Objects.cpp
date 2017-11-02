// Fill out your copyright notice in the Description page of Project Settings.

#include "Climbable_Objects.h"
#include "Components/BoxComponent.h"

// Sets default values
AClimbable_Objects::AClimbable_Objects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_ObjectRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); 
	RootComponent = m_ObjectRoot; 

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); 
	m_Mesh->SetupAttachment(m_ObjectRoot); 

	m_ClimbTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ClimbTrigger"));

	m_ClimbTrigger->SetupAttachment(m_ObjectRoot); 
}

// Called when the game starts or when spawned
void AClimbable_Objects::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClimbable_Objects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

