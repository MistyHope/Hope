// Fill out your copyright notice in the Description page of Project Settings.

#include "Trampoline.h"
#include "Components/BoxComponent.h"
#include "Misted_HopeCharacter.h"

// Sets default values
ATrampoline::ATrampoline()
	:m_JumpForce(2)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); 
	RootComponent = m_RootComponent; 

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); 
	m_Mesh->SetupAttachment(RootComponent); 

	m_BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	m_BoxTrigger->SetupAttachment(RootComponent); 
	m_BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATrampoline::OnOverlapBegin);
	m_BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &ATrampoline::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ATrampoline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrampoline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(m_bIsJumped)
		m_Character->TrampolineJump(m_JumpForce);

}


void ATrampoline::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass() == GetWorld()->GetFirstPlayerController()->GetPawn()->GetClass())
	{
		m_bIsJumped = true; 
	}
}

void ATrampoline::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	m_bIsJumped = false; 
}

