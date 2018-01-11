// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NextLevelTrigger.generated.h"

UCLASS()
class MISTED_HOPE_API ANextLevelTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANextLevelTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = Trigger)
		class UShapeComponent* m_TriggerBox; 
	UPROPERTY(EditAnywhere, Category = Trigger)
		class USceneComponent* m_RootComponent; 
	UPROPERTY(EditAnywhere, Category = Level)
		FName m_nextLevelName; 
	UPROPERTY(EditAnywhere, Category = Level)
		FName m_currentLevelName; 

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	
};
