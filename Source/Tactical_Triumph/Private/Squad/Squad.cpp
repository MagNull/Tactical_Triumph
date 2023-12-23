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
	UE_LOG(LogTemp, Display, TEXT("Post sBranch"));

	if (FindDropZone->Row != ESquadRow::Vanguard)
		OutForward = GetDropZone(static_cast<ESquadRow>(static_cast<int>(FindDropZone->Row) + 1),
		                         FindDropZone->Column)->GetHero();

	if (FindDropZone->Row != ESquadRow::Back)
		OutBack = GetDropZone(static_cast<ESquadRow>(static_cast<int>(FindDropZone->Row) - 1),
		                      FindDropZone->Column)->GetHero();
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

AHero* USquad::GetLeader()
{
	if(Leader == nullptr)
	{
		Leader = GetCenterDropZone()->GetHero();
	}
	return Leader;
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
	return {};
}

ADropZone* USquad::GetCenterDropZone()
{
	return GetDropZone(ESquadRow::Flank, ESquadColumn::Mid);
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

void USquad::OnSetHero(AHero* NewHero)
{
	UAbilitySystemComponent* TargetASC = NewHero->GetAbilitySystemComponent();
	for (auto Effect : SquadEffects)
	{
		TargetASC->ApplyGameplayEffectToSelf(Effect.GetDefaultObject(), 0, TargetASC->MakeEffectContext());
	}
	for (auto Ability : SquadAbilities)
	{
		TargetASC->GiveAbility(Ability.GetDefaultObject());
	}
}

void USquad::AddDropZone(ADropZone* NewDropZone)
{
	if (NewDropZone == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Failed to add drop zone"));
		return;
	}
	
	DropZones.Add(NewDropZone);
	OnSetHeroHandle = NewDropZone->OnSetHero.AddUObject(this, &USquad::OnSetHero);
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
