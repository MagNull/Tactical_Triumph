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
	UE_LOG(LogTemp, Display, TEXT("Start"));
	const ADropZone* FindDropZone = nullptr;

	for (const auto DropZone : DropZones)
	{
		if (DropZone->GetHero() == OriginHero)
		{
			FindDropZone = DropZone;
		}
	}

	UE_LOG(LogTemp, Display, TEXT("Branch"));
	if (FindDropZone == nullptr)
	{
		OutForward = nullptr;
		OutBack = nullptr;
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("Post Branch"));

	if (FindDropZone->Row != ESquadRow::Vanguard)
		OutForward = GetHero(static_cast<ESquadRow>(static_cast<int>(FindDropZone->Row) + 1), FindDropZone->Column);

	if (FindDropZone->Row != ESquadRow::Back)
		OutBack = GetHero(static_cast<ESquadRow>(static_cast<int>(FindDropZone->Row) - 1), FindDropZone->Column);
	UE_LOG(LogTemp, Display, TEXT("Hero is %hd"), OutForward == nullptr);
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

ESquadColumn USquad::GetColumn(AHero* Hero) const
{
	for (const auto DropZone : DropZones)
	{
		if (DropZone->GetHero() == Hero)
		{
			return DropZone->Column;
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

TArray<AHero*> USquad::GetHeroes() const
{
	TArray<AHero*> result;
	for (const auto DropZone : DropZones)
	{
		AHero* hero = DropZone->GetHero();
		if (hero != nullptr)
		{
			result.Add(hero);
		}
	}

	return result;
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
	UAbilitySystemComponent* TargetASC = NewDropZone->GetHero()->GetAbilitySystemComponent();
	for (auto Effect : SquadEffects)
	{
		TargetASC->ApplyGameplayEffectToSelf(Effect.GetDefaultObject(), 0, TargetASC->MakeEffectContext());
	}
	for (auto Ability : SquadAbilities)
	{
		TargetASC->GiveAbility(Ability.GetDefaultObject());
	}
	DropZones.Add(NewDropZone);
}

void USquad::AddSquadEffect(TSubclassOf<UGameplayEffect> Effect)
{
	SquadEffects.Add(Effect);
	for (const auto DropZone : DropZones)
	{
		UAbilitySystemComponent* TargetASC = DropZone->GetHero()->GetAbilitySystemComponent();
		TargetASC->ApplyGameplayEffectToSelf(Effect.GetDefaultObject(), 0, TargetASC->MakeEffectContext());
	}
}

void USquad::AddSquadAbility(TSubclassOf<UHeroGameplayAbility> Ability, bool activate)
{
	SquadAbilities.Add(Ability);
	for (const auto DropZone : DropZones)
	{
		UAbilitySystemComponent* TargetASC = DropZone->GetHero()->GetAbilitySystemComponent();
		if (activate)
		{
			const FGameplayAbilitySpecHandle AbilitySpec = TargetASC->GiveAbility(Ability.GetDefaultObject());
			TargetASC->TryActivateAbility(AbilitySpec);
		}
		else
		{
			TargetASC->GiveAbility(Ability.GetDefaultObject());
		}
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
