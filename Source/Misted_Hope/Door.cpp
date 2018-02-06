// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "Components/BoxComponent.h"
#include "Misted_HopeCharacter.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); 
	RootComponent = m_RootComponent; 

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); 
	m_Mesh->SetupAttachment(m_RootComponent); 


}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ADoor::OpenDoor(float DeltaSeconds, FRotator StartRotation, float angle, float interpSpeed)
{
	SetActorRotation(UKismetMathLibrary::RInterpTo(GetActorRotation(), StartRotation + FRotator(angle, 0, 0), DeltaSeconds, interpSpeed));
}