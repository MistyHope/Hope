// Fill out your copyright notice in the Description page of Project Settings.

#include "Checkpoint.h"
#include "Components/BoxComponent.h"
#include "CheckpointManager.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); 
	RootComponent = m_RootComponent;
	m_BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger")); 
	m_BoxTrigger->SetupAttachment(RootComponent);
	m_BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);
	m_BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &ACheckpoint::OnOverlapEnd);
	m_CheckpointManager = CreateDefaultSubobject<ACheckpointManager>(TEXT("CheckpointManager")); 

}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{

}


void ACheckpoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass() == GetWorld()->GetFirstPlayerController()->GetPawn()->GetClass())
	{
		m_CheckpointManager->SetCheckpoint(GetActorLocation());
	}
}

void ACheckpoint::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	this->Destroy();
}
