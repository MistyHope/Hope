// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SetBack.generated.h"

UCLASS()
class MISTED_HOPE_API ASetBack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASetBack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = SetBack)
		class USceneComponent* m_Root; 
	UPROPERTY(EditAnywhere, Category = SetBack)
		class UShapeComponent* m_TriggerBox; 
	UPROPERTY(EditAnywhere, Category = Setback)
		class ACheckpointManager* m_CPManager;


	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
};
