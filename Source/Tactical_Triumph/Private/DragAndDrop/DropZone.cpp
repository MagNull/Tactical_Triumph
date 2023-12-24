#include "DragAndDrop/DropZone.h"

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
	if(Hero == nullptr)
		return nullptr;
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
