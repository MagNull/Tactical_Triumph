#include "Squad/Squad.h"
#include "DragAndDrop/DropZone.h"
#include "AbilitySystem/SquadLines.h"
#include "AbilitySystem/Hero.h"

USquad::USquad()
{
	PrimaryComponentTick.bCanEverTick = true;
}

TArray<AHero*> USquad::GetHeroesInColumn(ESquadColumn column) const
{
	TArray<AHero*> ResultArray;
	for (const auto DropZone : DropZones)
	{
		if (DropZone->Column == column)
		{
			ResultArray.Add(DropZone->GetHero());
		}
	}
	return ResultArray;
}

void USquad::GetNeighbours(AHero* originHero, AHero* outForward, AHero* outBack) const
{
	const ADropZone* FindDropZone = nullptr;

	for (const auto DropZone : DropZones)
	{
		if (DropZone->GetHero() == originHero)
		{
			FindDropZone = DropZone;
		}
	}

	if (FindDropZone == nullptr)
	{
		outForward = nullptr;
		outBack = nullptr;
		return;
	}

	if (FindDropZone->Row != ESquadRow::Vanguard)
		outForward = GetDropZone(static_cast<ESquadRow>(static_cast<int>(FindDropZone->Row) + 1),
		                         FindDropZone->Column)->GetHero();

	if (FindDropZone->Row == ESquadRow::Back)
		outBack = GetDropZone(static_cast<ESquadRow>(static_cast<int>(FindDropZone->Row) - 1),
		                      FindDropZone->Column)->GetHero();
}

ESquadRow USquad::GetRow(AHero* hero) const
{
	for (const auto DropZone : DropZones)
	{
		if (DropZone->GetHero() == hero)
		{
			return DropZone->Row;
		}
	}
	return {};
}

TArray<AHero*> USquad::GetHeroesInRow(ESquadRow row) const
{
	TArray<AHero*> ResultArray;
	for (const auto DropZone : DropZones)
	{
		if (DropZone->Row == row)
		{
			ResultArray.Add(DropZone->GetHero());
		}
	}
	return ResultArray;
}

AHero* USquad::GetLeader() const
{
	return GetDropZone(ESquadRow::Vanguard, ESquadColumn::Mid)->GetHero();
}

UObject* USquad::GetPlayerOwner() const
{
	return nullptr;
}

ADropZone* USquad::GetDropZone(ESquadRow row, ESquadColumn column) const
{
	for (const auto DropZone : DropZones)
	{
		if (DropZone->Row == row && DropZone->Column == column)
		{
			return DropZone;
		}
	}
	return nullptr;
}

void USquad::AddDropZone(ADropZone* NewDropZone)
{
	if (NewDropZone == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Failed to add drop zone"));
		return;
	}
	DropZones.Add(NewDropZone);
}

// Called when the game starts or when spawned
void USquad::BeginPlay()
{
	Super::BeginPlay();
}

void USquad::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
