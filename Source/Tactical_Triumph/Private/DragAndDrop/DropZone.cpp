#include "DragAndDrop/DropZone.h"
#include "AbilitySystem/Hero.h"

// Sets default values
ADropZone::ADropZone()
{
	PrimaryActorTick.bCanEverTick = true;
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

	OnSetHero.Broadcast(NewHero);
}

bool ADropZone::IsCenter()
{
	return Column == ESquadColumn::Mid && Row == ESquadRow::Flank;
}
