// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAIController.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "BaseAIPawn.h"


ABaseAIController::ABaseAIController()
	:m_forwardGroundOffset(0)
	, m_groundOffset(0)
{

}


void ABaseAIController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);
	SetPawn(InPawn);
	if (InPawn->GetClass()->GetFName() == TEXT("SmallAIPawn"))
		baseAIPawn = Cast<ABaseAIPawn>(InPawn);
}

bool ABaseAIController::Move(const FVector location)
{


	FHitResult RV_HIT(ForceInit);
	FCollisionQueryParams RV_Query = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	FVector LineTraceDir;
	if (baseAIPawn)
		LineTraceDir = (GetPawn()->GetActorLocation() + GetPawn()->GetActorForwardVector() * (FVector(m_forwardGroundOffset, 0, 0) + baseAIPawn->GetCapsuleRadius()));
	else
		LineTraceDir = (GetPawn()->GetActorLocation() + GetPawn()->GetActorForwardVector() * 50);

	bool hitResult;
	if (baseAIPawn)
		hitResult = GetWorld()->LineTraceSingleByObjectType(RV_HIT, GetPawn()->GetActorLocation(), LineTraceDir - GetPawn()->GetActorUpVector() * baseAIPawn->GetCapsuleHalfHeight() + FVector(0, 0, m_groundOffset), ECC_WorldStatic);
	else
		hitResult = GetWorld()->LineTraceSingleByObjectType(RV_HIT, GetPawn()->GetActorLocation(), LineTraceDir - GetPawn()->GetActorUpVector() * 50, ECC_WorldStatic);

	DrawDebugLine(GetWorld(), GetPawn()->GetActorLocation(), LineTraceDir - GetPawn()->GetActorUpVector() * (FVector(0, 0, m_groundOffset) + baseAIPawn->GetCapsuleHalfHeight()), FColor::Black);
	if (hitResult)
	{
		MoveToLocation(location);
	}
	else
	{
		return false;
	}
	return false;
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
}


void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseAIController::Attack()
{

}

void ABaseAIController::SetGroundOffset(float value)
{
	m_groundOffset = value;
}

void ABaseAIController::SetForwardOffset(float value)
{
	m_forwardGroundOffset = value;
}