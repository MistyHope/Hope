// Fill out your copyright notice in the Description page of Project Settings.

#include "PushableBox.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Misted_HopeCharacter.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"


// Sets default values
APushableBox::APushableBox()
	: m_pushRight(false)
	,m_pushLeft(false)
	, m_attached(false)
	,m_Dist(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RootBox")); 
	RootComponent = m_RootBox; 

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); 
	m_Mesh->SetupAttachment(m_RootBox);


	m_TriggerBoxL = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerComponentL")); 
	m_TriggerBoxL->SetupAttachment(m_RootBox);
 				
	m_TriggerBoxL->OnComponentBeginOverlap.AddDynamic(this, &APushableBox::OnOverlapBeginL);
	m_TriggerBoxL->OnComponentEndOverlap.AddDynamic(this, &APushableBox::OnOverlapEndL);

	m_TriggerBoxR = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerComponentR")); 
	m_TriggerBoxR->SetupAttachment(m_RootBox); 

	m_TriggerBoxR->OnComponentBeginOverlap.AddDynamic(this, &APushableBox::OnOverlapBeginR);
	m_TriggerBoxR->OnComponentEndOverlap.AddDynamic(this, &APushableBox::OnOverlapEndR);
}

// Called when the game starts or when spawned
void APushableBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APushableBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FHitResult RV_HIT(ForceInit); 
	if (!GetWorld()->LineTraceSingleByChannel(RV_HIT, GetActorLocation() - FVector(m_RootBox->Bounds.BoxExtent.X, 0, m_RootBox->Bounds.BoxExtent.Z), GetActorLocation() - FVector(m_RootBox->Bounds.BoxExtent.X, 0, (m_RootBox->Bounds.BoxExtent.Z + 10)), ECC_WorldStatic) &&
		!GetWorld()->LineTraceSingleByChannel(RV_HIT, GetActorLocation() + FVector(m_RootBox->Bounds.BoxExtent.X, 0, -m_RootBox->Bounds.BoxExtent.Z), GetActorLocation() + FVector(m_RootBox->Bounds.BoxExtent.X, 0, (-m_RootBox->Bounds.BoxExtent.Z - 10)), ECC_WorldStatic))
	{
		m_RootBox->SetSimulatePhysics(true);
	}
	if (m_Char)
	{
		if (m_Char->m_bIsPushing && !m_attached)
		{
			if (FVector::Dist(GetActorLocation() - FVector(m_RootBox->Bounds.BoxExtent.X, 0, 0), m_Char->GetActorLocation() + FVector(m_Char->GetCapsuleComponent()->GetScaledCapsuleRadius())) < 20)
			{
				UE_LOG(LogTemp, Warning, TEXT("TooClose"));
				SetActorLocation(GetActorLocation() + FVector(25, 0, 0));
			}
			m_attached = m_RootBox->AttachToComponent(m_Char->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
			
		}
		else if(!m_Char->m_bIsPushing && m_attached)
		{
			m_RootBox->DetachFromComponent(FDetachmentTransformRules(FDetachmentTransformRules::KeepWorldTransform));
			m_attached = false; 
		}
	}
	else
	{
		m_RootBox->DetachFromComponent(FDetachmentTransformRules(FDetachmentTransformRules::KeepWorldTransform));
		m_attached = false;
	}
	
	//Changes the RootState of the object to provide the object to get moved from the character without getting grabbed
}

void APushableBox::OnOverlapBeginL(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	m_Char = Cast<AMisted_HopeCharacter>(OtherActor);
	if (m_Char)
	{
		m_RootBox->SetSimulatePhysics(false);
		m_pushLeft = true; 

	}
}


void APushableBox::OnOverlapEndL(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMisted_HopeCharacter* endChar = Cast<AMisted_HopeCharacter>(OtherActor);
	if(endChar && !m_attached)
	{
		m_Char = nullptr; 
		m_pushLeft = false;
	}
}

void APushableBox::OnOverlapBeginR(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	m_Char = Cast<AMisted_HopeCharacter>(OtherActor);
	if (m_Char)
	{
		m_RootBox->SetSimulatePhysics(false);
		m_pushRight = true; 
	}


}


void APushableBox::OnOverlapEndR(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMisted_HopeCharacter* endChar = Cast<AMisted_HopeCharacter>(OtherActor);
	if (endChar &&!m_attached)
	{
		m_Char = nullptr;
		m_pushRight = false; 
	}
}