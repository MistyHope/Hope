// Fill out your copyright notice in the Description page of Project Settings.

#include "PushableBox.h"
#include "Components/BoxComponent.h"
#include "Misted_HopeCharacter.h"

// Sets default values
APushableBox::APushableBox()
	:m_bIsGrabbed(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_RootObject = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); 
	RootComponent = m_RootObject; 

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); 
	m_Mesh->SetupAttachment(m_RootObject); 

	m_TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox")); 
	m_TriggerBox->SetWorldScale3D(FVector(1, 1, 1)); 
	m_TriggerBox->bGenerateOverlapEvents = true; 
	m_TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APushableBox::OnOverlapBegin); 
	m_TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APushableBox::OnOverlapEnd); 
	m_TriggerBox->SetupAttachment(m_RootObject); 

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
	
	//Changes the RootState of the object to provide the object to get moved from the character without getting grabbed
	if (!m_bIsGrabbed && !IsRootComponentStatic())
		m_RootObject->SetMobility(EComponentMobility::Static);
	else if (m_bIsGrabbed && IsRootComponentStatic())
		m_RootObject->SetMobility(EComponentMobility::Movable);
			
	UWorld* WorldRef = GetWorld();
	AMisted_HopeCharacter* Character = Cast<AMisted_HopeCharacter>(WorldRef->GetFirstPlayerController()->GetCharacter());
	UE_LOG(LogTemp, Warning, TEXT("IsPushing : %s"), Character->m_bIsPushing ? TEXT("True") : TEXT("False"))

	//UE_LOG(LogTemp, Warning, TEXT("Mobility %s"), IsRootComponentStatic() ? TEXT("True") : TEXT("False"));
}

void APushableBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UWorld* WorldRef = GetWorld(); 
	AMisted_HopeCharacter* Character = Cast<AMisted_HopeCharacter>(WorldRef->GetFirstPlayerController()->GetCharacter()); 
	if (Character)
	{
		if (Character->m_bIsPushing)
			m_bIsGrabbed = true;
		else
			m_bIsGrabbed = false;
	}

}
void APushableBox::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

