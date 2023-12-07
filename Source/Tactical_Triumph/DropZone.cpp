// Fill out your copyright notice in the Description page of Project Settings.


#include "DropZone.h"

// Sets default values
ADropZone::ADropZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADropZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADropZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ADropZone::GetIsOccupied()
{
	return IsOccupied;
}

AHero* ADropZone::GetHero()
{
	return Hero;
}

void ADropZone::SetHero(AHero* NewHero)
{
	if(NewHero == nullptr)
		return;
	
	Hero = NewHero;
	IsOccupied = true;
}







