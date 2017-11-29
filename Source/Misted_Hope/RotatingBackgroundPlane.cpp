// Fill out your copyright notice in the Description page of Project Settings.

#include "RotatingBackgroundPlane.h"


// Sets default values
ARotatingBackgroundPlane::ARotatingBackgroundPlane()
	:m_RotationValue(100)
	,m_RotationDegrees(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); 
	RootComponent = m_RootComponent; 

	m_Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane")); 
	m_Plane->SetupAttachment(RootComponent); 


}

// Called when the game starts or when spawned
void ARotatingBackgroundPlane::BeginPlay()
{ 
	Super::BeginPlay();
	m_CharStartPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	m_RotationDegrees = 360/(m_RotationValue*100);
	SetActorLocation(FVector(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z));
}

// Called every frame
void ARotatingBackgroundPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float rotate = m_CharStartPosition.X - GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation().X;
	SetActorRotation(FRotator(m_currentRotation.Pitch, m_currentRotation.Yaw - (m_RotationDegrees *rotate), m_currentRotation.Roll)); 
	SetActorLocation(FVector(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z));

}

