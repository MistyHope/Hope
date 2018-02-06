// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorChain.h"


// Sets default values
ADoorChain::ADoorChain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")); 
	RootComponent = m_Root; 

	m_DoorChain = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorChain")); 
	m_DoorChain->SetupAttachment(m_Root); 
}

// Called when the game starts or when spawned
void ADoorChain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorChain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

