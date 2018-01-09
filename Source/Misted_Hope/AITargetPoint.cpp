// Fill out your copyright notice in the Description page of Project Settings.

#include "AITargetPoint.h"
#include "BaseAICharacter.h"


AAITargetPoint::AAITargetPoint()
{
	m_BaseAICharacter = CreateDefaultSubobject<ABaseAICharacter>("BaseChar");
}


ABaseAICharacter* AAITargetPoint::GetCurrentChar()
{
	return m_BaseAICharacter;
}

