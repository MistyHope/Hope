// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HideSpots.generated.h"

UCLASS()
class MISTED_HOPE_API AHideSpots : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHideSpots();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Object)
		class USceneComponent* m_RootComponent; 
	UPROPERTY(EditAnywhere, Category = Object)
		class UStaticMeshComponent* m_Mesh; 
	UPROPERTY(EditAnywhere, Category = Trigger)
		class UBoxComponent* m_TriggerBox; 

};
