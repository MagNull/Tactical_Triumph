#include "Squad/Squad.h"

#include "DragAndDrop/DropZone.h"

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

void USquad::GetNeighbours(AHero* OriginHero, AHero* OutForward, AHero* OutBack) const
{
	const ADropZone* FindDropZone = nullptr;

	for (const auto DropZone : DropZones)
	{
		if (DropZone->GetHero() == OriginHero)
		{
			FindDropZone = DropZone;
		}
	}

	if (FindDropZone == nullptr)
	{
		OutForward = nullptr;
		OutBack = nullptr;
		return;
	}

	if (FindDropZone->Row != ESquadRow::Vanguard)
		OutForward = GetHero(static_cast<ESquadRow>(static_cast<int>(FindDropZone->Row) + 1), FindDropZone->Column);

	if (FindDropZone->Row != ESquadRow::Back)
		OutBack = GetHero(static_cast<ESquadRow>(static_cast<int>(FindDropZone->Row) - 1), FindDropZone->Column);
}

ESquadRow USquad::GetRow(AHero* Hero) const
{
	for (const auto DropZone : DropZones)
	{
		if (DropZone->GetHero() == Hero)
		{
			return DropZone->Row;
		}
	}
	return {};
}

TArray<AHero*> USquad::GetHeroesInRow(ESquadRow Row) const
{
	TArray<AHero*> ResultArray;
	for (const auto DropZone : DropZones)
	{
		if (DropZone->Row == Row)
		{
			ResultArray.Add(DropZone->GetHero());
		}
	}
	return ResultArray;
}

AHero* USquad::GetLeader() const
{
	return GetHero(ESquadRow::Flank, ESquadColumn::Mid);
}

UObject* USquad::GetPlayerOwner() const
{
	return nullptr;
}

void USquad::AddHero(ADropZone* NewDropZone)
{
	const AHero* Hero = NewDropZone->GetHero();
	for (auto EffectSpec : SquadEffects)
	{
		Hero->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data);
	}
	DropZones.Add(NewDropZone);
}

void USquad::AddSquadEffect(FGameplayEffectSpecHandle EffectSpec)
{
	SquadEffects.Add(EffectSpec);
	for (const auto DropZone : DropZones)
	{
		AHero* Hero = DropZone->GetHero();
		Hero->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data);
		UE_LOG(LogTemp, Display, TEXT("Hero %s get %s"), *Hero->GetName(), *EffectSpec.Data->ToSimpleString())
	}
}

AHero* USquad::GetHero(ESquadRow Row, ESquadColumn Column) const
{
	for (const auto DropZone : DropZones)
	{
		if (DropZone->Row == Row && DropZone->Column == Column)
		{
			return DropZone->GetHero();
		}
	}
	return nullptr;
}