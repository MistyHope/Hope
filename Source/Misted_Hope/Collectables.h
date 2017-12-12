// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectables.generated.h"

UCLASS()
class MISTED_HOPE_API ACollectables : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectables();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Collectable)
		class USceneComponent* m_Root; 
	UPROPERTY(EditAnywhere, Category = Collectable)
		class UStaticMeshComponent* m_Mesh; 
	UPROPERTY(EditAnywhere, Category = Collectable)
		class UShapeComponent* m_Trigger; 

	UFUNCTION()
		void Collect();
};
