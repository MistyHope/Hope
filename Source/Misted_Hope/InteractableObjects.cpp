// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableObjects.h"
#include "Components/BoxComponent.h"

// Sets default values
AInteractableObjects::AInteractableObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent")); 
	RootComponent = m_BoxComponent; 

}

// Called when the game starts or when spawned
void AInteractableObjects::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

