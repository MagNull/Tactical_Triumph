// Fill out your copyright notice in the Description page of Project Settings.


#include "Squad.h"

// Sets default values
USquad::USquad()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

TArray<AHero*> USquad::GetHeroesInColumn(EColumn column) const
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

	if (FindDropZone->Row != ERow::Vanguard)
		outForward = GetHero(static_cast<ERow>(static_cast<int>(FindDropZone->Row) + 1), FindDropZone->Column);

	if (FindDropZone->Row == ERow::Back)
		outBack = GetHero(static_cast<ERow>(static_cast<int>(FindDropZone->Row) - 1), FindDropZone->Column);
}

ERow USquad::GetRow(AHero* hero) const
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

TArray<AHero*> USquad::GetHeroesInRow(ERow row) const
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
	return GetHero(ERow::Vanguard, EColumn::Mid);
}

UObject* USquad::GetPlayerOwner() const
{
	return nullptr;
}

void USquad::AddHero(ADropZone* NewDropZone)
{
	DropZones.Add(NewDropZone);
}

AHero* USquad::GetHero(ERow row, EColumn column) const
{
	for (const auto DropZone : DropZones)
	{
		if (DropZone->Row == row && DropZone->Column == column)
		{
			return DropZone->GetHero();
		}
	}
	return nullptr;
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
