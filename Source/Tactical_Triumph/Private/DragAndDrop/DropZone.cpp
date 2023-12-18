#include "DragAndDrop/DropZone.h"
#include "AbilitySystem/Hero.h"

// Sets default values
ADropZone::ADropZone()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADropZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADropZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ADropZone::GetIsOccupied() const
{
 	return Hero != nullptr;
}

AHero* ADropZone::GetHero() const
{
	return Hero;
}

void ADropZone::SetHero(AHero* NewHero)
{
	if(NewHero == nullptr)
		return;
	
	Hero = NewHero;
}
