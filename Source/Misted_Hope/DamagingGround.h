// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamagingGround.generated.h"

UCLASS()
class MISTED_HOPE_API ADamagingGround : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamagingGround();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Ground)
		class UStaticMeshComponent* m_Mesh; 
	UPROPERTY(EditAnywhere, Category = Ground)
		class USceneComponent* m_RootComponent; 
	UPROPERTY(EditAnywhere, Category = Ground)
		class UShapeComponent* m_Trigger; 
	
	FTimerHandle m_TimerHandle; 
	UPROPERTY(EditAnywhere, Category = Damage)
		float m_DamageDelay; 

	class AMisted_HopeCharacter* m_Character; 

	bool m_DamagePlayer; 

	UPROPERTY(EditAnywhere, Category = Damage)
		float m_DamageValue; 

	UFUNCTION()
		void HurtCharacter();

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
