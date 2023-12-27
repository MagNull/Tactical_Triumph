#include "DragAndDrop/DropZone.h"

ADropZone::ADropZone()
{
	PrimaryActorTick.bCanEverTick = true;
}

int ADropZone::GetRowInt() const
{
	return static_cast<int>(Row);
}

int ADropZone::GetColumnInt() const
{
	return static_cast<int>(Column);
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
	if (NewHero == nullptr)
		return;

	Hero = NewHero;

	OnSetHero.Broadcast(NewHero);
}

bool ADropZone::IsCenter()
{
	return Column == ESquadColumn::Mid && Row == ESquadRow::Flank;
}

APlayerPawn* ADropZone::GetPlayerOwner()
{
	return PlayerOwnerPawn;
}

void ADropZone::Clear()
{
	Hero = nullptr;
}
