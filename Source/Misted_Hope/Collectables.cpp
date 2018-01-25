// Fill out your copyright notice in the Description page of Project Settings.

#include "Collectables.h"
#include "Components/BoxComponent.h"
#include "Misted_HopeCharacter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACollectables::ACollectables()
	:m_HoverHeight(5)
	,m_ReachedTop(false)
	,m_HoverSpeed(1)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")); 
	RootComponent = m_Root; 

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); 
	m_Mesh->SetupAttachment(RootComponent); 

	m_Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	m_Trigger->SetupAttachment(RootComponent); 
	m_Trigger->OnComponentBeginOverlap.AddDynamic(this, &ACollectables::OnOverlapBegin);
	m_Trigger->OnComponentEndOverlap.AddDynamic(this, &ACollectables::OnOverlapEnd);


}

// Called when the game starts or when spawned
void ACollectables::BeginPlay()
{
	Super::BeginPlay();
	m_StartPosition = GetActorLocation();
}

// Called every frame
void ACollectables::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!m_ReachedTop)
	{
		SetActorLocation(UKismetMathLibrary::VInterpTo(GetActorLocation(), m_StartPosition + FVector(0, 0, m_HoverHeight), DeltaTime, m_HoverSpeed));
		if (FVector::Dist(GetActorLocation(), m_StartPosition + FVector(0, 0, m_HoverHeight)) < 1)
			m_ReachedTop = true;
	}
	else
	{
		SetActorLocation(UKismetMathLibrary::VInterpTo(GetActorLocation(), m_StartPosition, DeltaTime, m_HoverSpeed));
		if (FVector::Dist(GetActorLocation(), m_StartPosition) < 1)
			m_ReachedTop = false;
	}
}

void ACollectables::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMisted_HopeCharacter* character = Cast<AMisted_HopeCharacter>(OtherActor);
	if (character)
	{
		character->Collect(m_CurrentCollectable);
		this->Destroy();
	}
}
void ACollectables::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}