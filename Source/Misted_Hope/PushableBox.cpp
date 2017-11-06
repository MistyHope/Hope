// Fill out your copyright notice in the Description page of Project Settings.

#include "PushableBox.h"
#include "Components/BoxComponent.h"
#include "Misted_HopeCharacter.h"

// Sets default values
APushableBox::APushableBox()

{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); 
	m_Mesh->SetupAttachment(RootComponent); 

	m_TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerComponent")); 
	m_TriggerBox->SetupAttachment(RootComponent); 
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
}


void APushableBox::PushObject(float amount, FVector direction)
{
	UPrimitiveComponent* prim = GetRootPrimitiveComponent(); 
	UE_LOG(LogTemp, Warning, TEXT("Root: %s"), *prim->GetFName().ToString()); 
	//UE_LOG(LogTemp, Warning, TEXT("Primitive : %s"), *primitive->GetFName().ToString()); 

}

void APushableBox::PullObject(float amount, FVector direction)
{

}




