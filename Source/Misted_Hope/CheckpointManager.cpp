// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckpointManager.h"
#include "Misted_HopeCharacter.h"

// Sets default values
ACheckpointManager::ACheckpointManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ACheckpointManager::BeginPlay()
{
	Super::BeginPlay();
	m_currentCheckpointPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	m_Char = Cast<AMisted_HopeCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter()); 
	m_currentPlayerHope = m_Char->GetPlayerHope();
}

// Called every frame
void ACheckpointManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation().Z < -900)
		GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(m_currentCheckpointPos);
}

void ACheckpointManager::SetCheckpoint(const FVector& vec)
{
	m_Char = Cast<AMisted_HopeCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	m_currentCheckpointPos = vec; 
	m_currentPlayerHope = m_Char->GetPlayerHope();

}

void ACheckpointManager::SetCharacterToCP(AMisted_HopeCharacter* Character)
{
	Character->ResetChar(m_currentCheckpointPos);
	Character->SetPlayerHope(m_currentPlayerHope);
}