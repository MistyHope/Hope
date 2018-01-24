// Fill out your copyright notice in the Description page of Project Settings.

#include "BridgePiece.h"
#include "Components/BoxComponent.h"


UBridgePiece::UBridgePiece()
{
	m_RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RootBox")); 
	
	m_BridgePiece = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); 
	m_BridgePiece->SetupAttachment(m_RootBox);

}


