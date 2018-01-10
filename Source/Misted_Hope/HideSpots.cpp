// Fill out your copyright notice in the Description page of Project Settings.

#include "HideSpots.h"
#include "Components/BoxComponent.h"
#include "Misted_HopeCharacter.h"

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
	m_TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AHideSpots::OnOverlapBegin); 
	m_TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AHideSpots::OnOverlapEnd);
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

void AHideSpots::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass() == GetWorld()->GetFirstPlayerController()->GetClass())
	{
		AMisted_HopeCharacter* Character = Cast<AMisted_HopeCharacter>(OtherActor);
		Character->m_isVisible = false;
	}
}

void AHideSpots::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetClass() == GetWorld()->GetFirstPlayerController()->GetClass())
	{
		AMisted_HopeCharacter* Character = Cast<AMisted_HopeCharacter>(OtherActor);
		Character->m_isVisible = true;
	}
}


