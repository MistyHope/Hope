// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Climbable_Objects.generated.h"

UCLASS()
class MISTED_HOPE_API AClimbable_Objects : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClimbable_Objects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Climbable)
		class USceneComponent* m_ObjectRoot; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Climbable)
		class UStaticMeshComponent* m_Mesh;  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Climbable)
		class UShapeComponent* m_ClimbTrigger;

	
	
};
