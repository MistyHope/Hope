// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class MISTED_HOPE_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Door)
		class USceneComponent* m_RootComponent; 
	UPROPERTY(EditAnywhere, Category = Door)
		class UStaticMeshComponent* m_Mesh; 

	UFUNCTION()
		void OpenDoor(float DeltaSeconds, FRotator StartRotation, float angle, float interpSpeed);
};
