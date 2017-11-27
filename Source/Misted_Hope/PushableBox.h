// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObjects.h"
#include "PushableBox.generated.h"

class UBoxComponent;

UCLASS(config=Game)
class  APushableBox : public AInteractableObjects
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APushableBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Object)
		class UStaticMeshComponent* m_Mesh;
	UPROPERTY(EditAnywhere, Category = Object)
		class UShapeComponent* m_TriggerBox; 
};
