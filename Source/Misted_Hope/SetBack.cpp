// Fill out your copyright notice in the Description page of Project Settings.

#include "SetBack.h"
#include "Components/BoxComponent.h"
#include "Misted_HopeCharacter.h"
#include "CheckpointManager.h"

// Sets default values
ASetBack::ASetBack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); 
	RootComponent = m_Root; 

	m_TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	m_TriggerBox->SetupAttachment(RootComponent);
	m_TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASetBack::OnOverlapBegin);

	m_CPManager = CreateDefaultSubobject<ACheckpointManager>(TEXT("CPManager")); 
}

// Called when the game starts or when spawned
void ASetBack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASetBack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASetBack::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMisted_HopeCharacter* character = Cast<AMisted_HopeCharacter>(OtherActor); 
	if (character)
	{
		m_CPManager->SetCharacterToCP(character);
	}
}
