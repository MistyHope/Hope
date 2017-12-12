// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAIController.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"


void ABaseAIController::Possess(class APawn* InPawn)
{
	SetPawn(InPawn); 
	this->Possess(InPawn); 
}

bool ABaseAIController::Move(const FVector location)
{
	FHitResult RV_HIT(ForceInit);
	FCollisionQueryParams RV_Query = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	FVector LineTraceDir = (GetPawn()->GetActorLocation() + GetPawn()->GetActorForwardVector() * 50);
	bool hitResult = GetPawn()->ActorLineTraceSingle(RV_HIT, LineTraceDir, LineTraceDir - GetPawn()->GetActorUpVector() * 50, ECC_WorldStatic, RV_Query);
	if (hitResult)
	{
		MoveToLocation(location);
		return true;
	}
	else
	{
		return false;
	}
	return true;
}

void ABaseAIController::Attack()
{

}