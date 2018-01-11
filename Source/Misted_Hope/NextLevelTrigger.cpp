// Fill out your copyright notice in the Description page of Project Settings.

#include "NextLevelTrigger.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANextLevelTrigger::ANextLevelTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_RootComponent = CreateDefaultSubobject<USceneComponent>("Root"); 
	RootComponent= m_RootComponent;

	m_TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox"); 

	m_TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ANextLevelTrigger::OnOverlapBegin);
	m_TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ANextLevelTrigger::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ANextLevelTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANextLevelTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANextLevelTrigger::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UWorld* currentWorld = GetWorld();
	if (OtherActor->GetClass() == currentWorld->GetFirstPlayerController()->GetClass())
	{
		if (m_currentLevelName.ToString() == currentWorld->GetMapName())
		{
			UGameplayStatics::OpenLevel(currentWorld, m_nextLevelName);
		}
		else
		{
			UGameplayStatics::OpenLevel(currentWorld, m_currentLevelName);
		}
		
	}

}

void ANextLevelTrigger::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}

