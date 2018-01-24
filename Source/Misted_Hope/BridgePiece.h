// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BridgePieces.h"
#include "BridgePiece.generated.h"

/**
 * 
 */
UCLASS()
class MISTED_HOPE_API UBridgePiece : public UBridgePieces
{
	GENERATED_BODY()
	
public: 
	UBridgePiece();

	UPROPERTY(EditAnywhere, Category = "BridgePiece")
		class UStaticMeshComponent* m_BridgePiece; 
	UPROPERTY(EditAnywhere, Category = "BridgePiece")
		class UShapeComponent* m_RootBox; 
	
	
};
