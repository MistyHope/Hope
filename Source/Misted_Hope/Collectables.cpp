// Fill out your copyright notice in the Description page of Project Settings.

#include "Collectables.h"
#include "Components/BoxComponent.h"
#include "Misted_HopeCharacter.h"

// Sets default values
ACollectables::ACollectables()
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
	
}

// Called every frame
void ACollectables::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void ACollectables::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass() == GetWorld()->GetFirstPlayerController()->GetPawn()->GetClass())
	{
		AMisted_HopeCharacter* character = Cast<AMisted_HopeCharacter>(OtherActor);
		character->Collect(m_CurrentCollectable);
	}
}
void ACollectables::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	this->Destroy();
}