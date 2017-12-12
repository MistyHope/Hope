// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallingTree.generated.h"

UCLASS()
class MISTED_HOPE_API AFallingTree : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFallingTree();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool m_isFell; 

	UPROPERTY(EditAnywhere, Category = Tree)
		float m_FallingSpeed; 

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UPROPERTY(EditAnywhere, Category = Tree)
		class UStaticMeshComponent* m_Tree;
	UPROPERTY(EditAnywhere, Category = Trigger)
		class USceneComponent* m_RootComponent; 
	UPROPERTY(EditAnywhere, Category = Trigger)
		class UBoxComponent* m_TriggerBox; 
	UPROPERTY(EditAnywhere, Category = Tree)
		class UBoxComponent* m_TreeCollider;

	
	
};
