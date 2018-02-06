// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CompleteDoor.generated.h"

UCLASS()
class MISTED_HOPE_API ACompleteDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACompleteDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = Root)
		class USceneComponent* m_Root; 
	UPROPERTY(EditAnywhere, Category = Door)
		class ADoor* m_doorLeft; 
	UPROPERTY(EditAnywhere, Category = Door)
		class ADoor* m_doorRight; 
	UPROPERTY(EditAnywhere, Category = Door)
		class ADoorChain* m_ChainMesh; 
	UPROPERTY(EditAnywhere, Category = Door)
		class UShapeComponent* m_TriggerBox; 
	UPROPERTY(EditAnywhere, Category = Door)
		float m_interSpeedL;
	UPROPERTY(EditAnywhere, Category = Door)
		float m_interSpeedR;
	UPROPERTY(EditAnywhere, Category = Door)
		float m_angleL;
	UPROPERTY(EditAnywhere, Category = Door)
		float m_angleR;
	UPROPERTY()
		FRotator m_StartRotationL;
	UPROPERTY()
		FRotator m_StartRotationR;
	UPROPERTY()
		bool m_isOpen;
	
};
