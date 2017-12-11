// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnumAndStructHolder.generated.h"
/**
 * 
 */

UENUM(BlueprintType)
enum ECollectables
{
	NormalHerb, 
	SpecialHerb
};

UENUM(BlueprintType)
enum class EInteractions : uint8
{
	Hide
	, Push
};