// Fill out your copyright notice in the Description page of Project Settings.

#include "Collectables.h"
#include "Components/BoxComponent.h"

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


void ACollectables::Collect()
{

}
