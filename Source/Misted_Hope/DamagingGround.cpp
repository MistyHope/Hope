// Fill out your copyright notice in the Description page of Project Settings.

#include "DamagingGround.h"
#include "Components/BoxComponent.h"
#include "Misted_HopeCharacter.h"

// Sets default values
ADamagingGround::ADamagingGround()
	:m_DamageDelay(1)
	,m_DamageValue(5)
	,m_DamagePlayer(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); 
	RootComponent = m_RootComponent; 

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); 
	m_Mesh->SetupAttachment(RootComponent); 

	m_Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger")); 
	m_Trigger->SetupAttachment(RootComponent); 
	m_Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADamagingGround::OnOverlapBegin);
	m_Trigger->OnComponentEndOverlap.AddDynamic(this, &ADamagingGround::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ADamagingGround::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamagingGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!m_DamagePlayer)
		GetWorldTimerManager().SetTimer(m_TimerHandle, this, &ADamagingGround::HurtCharacter, m_DamageDelay, true);


}

void ADamagingGround::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->GetClass() == GetWorld()->GetFirstPlayerController()->GetPawn()->GetClass())
	{
		m_Character = Cast<AMisted_HopeCharacter>(OtherActor);
		m_DamagePlayer = true; 
	}

}
void ADamagingGround::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetClass() == GetWorld()->GetFirstPlayerController()->GetPawn()->GetClass())
	{
		m_DamagePlayer = false;
	}
	m_Character = nullptr;

}


void ADamagingGround::HurtCharacter()
{
	if(m_Character)
		m_Character->Hurt(m_DamageValue);
}