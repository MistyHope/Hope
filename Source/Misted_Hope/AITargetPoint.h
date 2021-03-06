// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "AITargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class MISTED_HOPE_API AAITargetPoint : public ATargetPoint
{
	GENERATED_BODY()

		AAITargetPoint();
	
	public:
		UPROPERTY(EditAnywhere, Category = Controller)
			class ABaseAICharacter* m_BaseAICharacter;

		UFUNCTION()
			ABaseAICharacter* GetCurrentChar();

};
