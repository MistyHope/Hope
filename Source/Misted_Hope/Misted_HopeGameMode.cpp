// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Misted_HopeGameMode.h"
#include "Misted_HopeCharacter.h"
#include "Blueprint/UserWidget.h"

AMisted_HopeGameMode::AMisted_HopeGameMode()
	:m_MasterVolume(1)
	,m_EffectVolume(1)
{
	// Set default pawn class to our character
	DefaultPawnClass = AMisted_HopeCharacter::StaticClass();


}


