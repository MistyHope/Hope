// Fill out your copyright notice in the Description page of Project Settings.

#include "FallingTree.h"
#include "Components/BoxComponent.h"

// Sets default values
AFallingTree::AFallingTree()
	:m_isFell(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); 
	RootComponent = m_RootComponent; 

	m_TreeCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("TreeRoot"));
	m_TreeCollider->SetupAttachment(RootComponent);

	m_Tree = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tree")); 
	m_Tree->SetupAttachment(m_TreeCollider);
	m_Tree->SetMobility(EComponentMobility::Movable);


	m_TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox")); 
	m_TriggerBox->SetupAttachment(RootComponent); 
	m_TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFallingTree::OnOverlapBegin); 
	m_TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AFallingTree::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AFallingTree::BeginPlay()
{
	Super::BeginPlay();
	m_isFell = false; 
	
}

// Called every frame
void AFallingTree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_isFell)
	{
		m_TreeCollider->SetEnableGravity(true);
		m_TreeCollider->SetSimulatePhysics(true);
	}
}

void AFallingTree::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass() == GetWorld()->GetFirstPlayerController()->GetPawn()->GetClass())
		m_isFell = true;

}
void AFallingTree::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
