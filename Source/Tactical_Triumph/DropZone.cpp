#include "DropZone.h"

ADropZone::ADropZone()
{
	PrimaryActorTick.bCanEverTick = true;

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







