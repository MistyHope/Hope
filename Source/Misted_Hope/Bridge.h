// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bridge.generated.h"

UCLASS()
class MISTED_HOPE_API ABridge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABridge();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = Bridge)
		class USceneComponent* m_RootComponent; 
	
	UPROPERTY(EditAnywhere, Category = Bridge)
		TArray<UStaticMesh*> m_BridgePieces; 
	UPROPERTY(EditAnywhere, Category = Trigger)
		class UBoxComponent* m_TriggerBox; 


	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);




	
};
