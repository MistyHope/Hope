// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointManager.generated.h"

UCLASS()
class MISTED_HOPE_API ACheckpointManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpointManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class AMisted_HopeCharacter* m_Char; 
	FVector m_currentCheckpointPos; 
	int m_currentPlayerHope; 
	
	UFUNCTION()
		void SetCheckpoint(const FVector& vec); 
	UFUNCTION()
		void SetCharacterToCP(class AMisted_HopeCharacter* character);
	
};
