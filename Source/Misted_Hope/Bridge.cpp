// Fill out your copyright notice in the Description page of Project Settings.

#include "Bridge.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABridge::ABridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); 
	RootComponent = m_RootComponent; 

	for (int i = 0; i < m_BridgePieces.Num(); i++)
	{
		m_BridgePieces[i] = CreateDefaultSubobject<UStaticMesh>(TEXT("Piece")); 
	}


	m_TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox")); 
	m_TriggerBox->SetupAttachment(RootComponent); 
}

// Called when the game starts or when spawned
void ABridge::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void ABridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABridge::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

