// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingBackgroundPlane.generated.h"

UCLASS()
class MISTED_HOPE_API ARotatingBackgroundPlane : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingBackgroundPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = Plane)
		class USceneComponent* m_RootComponent; 
	UPROPERTY(EditAnywhere, Category = Plane)
		class UStaticMeshComponent* m_Plane; 
	UPROPERTY(EditAnywhere, Category = Rotation)
		float m_RotationValue; 
	
	float m_RotationDegrees; 
	FVector m_CharStartPosition; 
	FRotator m_currentRotation; 

	
	
};
