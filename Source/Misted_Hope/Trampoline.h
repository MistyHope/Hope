// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trampoline.generated.h"

UCLASS()
class MISTED_HOPE_API ATrampoline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrampoline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = Object)
		class USceneComponent* m_RootComponent; 
	UPROPERTY(EditAnywhere, Category = Object)
		class UStaticMeshComponent* m_Mesh; 
	UPROPERTY(EditAnywhere, Category = Object)
		class UBoxComponent* m_BoxTrigger; 
	UPROPERTY(EditAnywhere, Category = Jump)
		float m_JumpForce; 
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, Category = Character)
		class AMisted_HopeCharacter* m_Character; 
	bool m_bIsJumped; 
};
