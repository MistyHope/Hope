// Fill out your copyright notice in the Description page of Project Settings.

#include "HideSpots.h"
#include "Components/BoxComponent.h"

// Sets default values
AHideSpots::AHideSpots()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); 
	RootComponent = m_RootComponent; 

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); 
	m_Mesh->SetupAttachment(RootComponent);

	m_TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger")); 
	m_TriggerBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHideSpots::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHideSpots::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



