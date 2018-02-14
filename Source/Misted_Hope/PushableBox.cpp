// Fill out your copyright notice in the Description page of Project Settings.

#include "PushableBox.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Misted_HopeCharacter.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"


// Sets default values
APushableBox::APushableBox()
	: m_pushRight(false)
	, m_pushLeft(false)
	, m_attached(false)
	, m_Dist(0)
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
	else
		m_RootBox->SetSimulatePhysics(false);

	if (m_Char)
	{
		FHitResult RV_HIT2(ForceInit);
		bool hitResult2;

		if (m_attached && m_pushRight)
		{
			FCollisionQueryParams params;
			params.AddIgnoredActor(this);
			params.AddIgnoredComponent(m_TriggerBoxL);
			DrawDebugLine(GetWorld(), GetActorLocation() - FVector(m_RootBox->Bounds.BoxExtent.X, 0, 0), GetActorLocation() - FVector(m_RootBox->Bounds.BoxExtent.X + 20, 0, 0), FColor::Black);
			hitResult2 = GetWorld()->LineTraceSingleByChannel(RV_HIT2, GetActorLocation() - FVector(m_RootBox->Bounds.BoxExtent.X, 0, 0), GetActorLocation() - FVector(m_RootBox->Bounds.BoxExtent.X + 5, 0, 0), ECC_WorldStatic, params);
			if (hitResult2)
			{
				m_Char->m_cantWalkLeft = true;
			}
			else
				m_Char->m_cantWalkLeft = false;
		}
		else if (m_attached && m_pushLeft)
		{
			FCollisionQueryParams params;
			params.AddIgnoredActor(this);
			params.AddIgnoredComponent(m_TriggerBoxR);
			DrawDebugLine(GetWorld(), GetActorLocation() + FVector(m_RootBox->Bounds.BoxExtent.X, 0, 0), GetActorLocation() + FVector(m_RootBox->Bounds.BoxExtent.X + 20, 0, 0), FColor::Black);
			hitResult2 = GetWorld()->LineTraceSingleByChannel(RV_HIT2, GetActorLocation() + FVector(m_RootBox->Bounds.BoxExtent.X, 0, 0), GetActorLocation() + FVector(m_RootBox->Bounds.BoxExtent.X + 5, 0, 0), ECC_WorldStatic, params);
			if (hitResult2)
			{
				m_Char->m_cantWalkRight = true;
			}
			else
				m_Char->m_cantWalkRight = false;
		}

		if (m_Char->m_bIsPushing && !m_attached)
		{
			if (m_pushLeft && m_Char->m_bLookRight)
			{
				m_attached = m_RootBox->AttachToComponent(m_Char->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
			}
			else if (m_pushRight && !m_Char->m_bLookRight)
			{
				m_attached = m_RootBox->AttachToComponent(m_Char->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
			}
			else
				m_Char->m_bIsPushing = false; 
		}
		else if (!m_Char->m_bIsPushing && m_attached)
		{
			m_RootBox->DetachFromComponent(FDetachmentTransformRules(FDetachmentTransformRules::KeepWorldTransform));
			m_attached = false;
		}
	}


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
	if (endChar && !m_attached)
	{
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
	if (endChar && !m_attached)
	{
		m_pushRight = false;
	}
}