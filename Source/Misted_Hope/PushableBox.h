// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObjects.h"
#include "PushableBox.generated.h"


UCLASS()
class  APushableBox : public AActor
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
		class UShapeComponent* m_RootBox; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = Object)
		class UStaticMeshComponent* m_Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Object)
		class UShapeComponent* m_TriggerBoxL;
	UPROPERTY(EditAnywhere, Category = Object)
		class UShapeComponent* m_TriggerBoxR; 
	UPROPERTY()
		bool m_pushRight; 
	UPROPERTY()
		bool m_pushLeft; 
	UPROPERTY()
		float m_Dist;
	UPROPERTY()
		bool m_attached; 
	UPROPERTY()
		class AMisted_HopeCharacter* m_Char; 

	UFUNCTION()
		void OnOverlapBeginL(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEndL(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void OnOverlapBeginR(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEndR(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
