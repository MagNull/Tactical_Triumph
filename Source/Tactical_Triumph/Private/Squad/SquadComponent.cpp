#include "Squad/SquadComponent.h"

#include "DragAndDrop/DropZone.h"

bool FSquadAbility::operator==(const FSquadAbility& other) const
{
	return other.SourceAbility == SourceAbility &&
		other.Ability == Ability;
}

bool FSquadEffect::operator==(const FSquadEffect& other) const
{
	return other.SourceAbility == SourceAbility &&
		other.EffectSpecHandle == EffectSpecHandle;
}

USquadComponent::USquadComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USquadComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto DropZone : DropZones)
	{
		DropZone->Clear();
		OnSetHeroHandle = DropZone->OnSetHero.AddUObject(
			this, &USquadComponent::OnSetHero);
	}
}

void USquadComponent::BeginDestroy()
{
	Super::BeginDestroy();

	for (auto DropZone : DropZones)
	{
		DropZone->OnSetHero.Remove(OnSetHeroHandle);
	}
}

void USquadComponent::RemoveHero(AHero* Hero)
{
	ADropZone* DropZone = GetDropZoneByHero(Hero);
	DropZone->Clear();
	Hero->GetAbilitySystemComponent()->ClearAllAbilities();
	Hero->Destroy();
}

bool USquadComponent::TryMoveHeroTo(AHero* Hero, ESquadRow row, ESquadColumn column)
{
	ADropZone* TargetDropZone = GetDropZone(row, column);
	if (TargetDropZone->IsOccupied())
	{
		UE_LOG(LogTemp, Warning, TEXT("Target drop zone is occupied"));
		return false;
	}

	const ESquadColumn HeroColumn = GetColumn(Hero);
	const ESquadRow HeroRow = GetRow(Hero);
	ADropZone* OldDropZone = GetDropZone(HeroRow, HeroColumn);
	if (!OldDropZone->IsOccupied())
	{
		UE_LOG(LogTemp, Warning, TEXT("Old drop zone is not occupied"));
		return false;
	}

	OldDropZone->Clear();
	TargetDropZone->SetHero(Hero);
	return true;
}

TArray<AHero*> USquadComponent::GetHeroes() const
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

TArray<AHero*> USquadComponent::GetHeroesInColumn(ESquadColumn column) const
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

TArray<AHero*> USquadComponent::GetHeroesInRow(ESquadRow Row) const
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

//TODO: Replace with 1 method instead zones and heroes
TArray<ADropZone*> USquadComponent::GetDropZonesInRow(ESquadRow Row) const
{
	TArray<ADropZone*> ResultArray;
	for (const auto DropZone : DropZones)
	{
		if (DropZone->Row == Row)
		{
			ResultArray.Add(DropZone);
		}
	}
	return ResultArray;
}

TArray<ADropZone*> USquadComponent::GetDropZonesInColumn(ESquadColumn Column) const
{
	TArray<ADropZone*> ResultArray;
	for (const auto DropZone : DropZones)
	{
		if (DropZone->Column == Column)
		{
			ResultArray.Add(DropZone);
		}
	}
	return ResultArray;
}

void USquadComponent::GetNeighbours(AHero* OriginHero, ADropZone*& OutForward, ADropZone*& OutBack) const
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
	{
		auto DropZone = GetDropZone(static_cast<ESquadRow>(static_cast<int>(FindDropZone->Row) - 1),
		                            FindDropZone->Column);
		if (DropZone == nullptr)
		{
			UE_LOG(LogTemp, Display, TEXT("DropZone is nullptr"));
			return;
		}
		OutForward = DropZone;
	}


	if (FindDropZone->Row != ESquadRow::Back)
	{
		auto DropZone = GetDropZone(static_cast<ESquadRow>(static_cast<int>(FindDropZone->Row) + 1),
		                            FindDropZone->Column);
		if (DropZone == nullptr)
		{
			UE_LOG(LogTemp, Display, TEXT("DropZone is nullptr"));
			return;
		}
		OutBack = DropZone;
	}
}

ADropZone* USquadComponent::GetForwardNeighbour(AHero* OriginHero)
{
	ADropZone *Forward = nullptr, *Back = nullptr;
	GetNeighbours(OriginHero, Forward, Back);
	UE_LOG(LogTemp, Display, TEXT("%hd"), Forward == nullptr)
	if (Forward == nullptr)
		return nullptr;

	return Forward;
}

ADropZone* USquadComponent::GetBackNeighbour(AHero* OriginHero)
{
	ADropZone *Forward = nullptr, *Back = nullptr;
	GetNeighbours(OriginHero, Forward, Back);

	if (Back == nullptr)
		return nullptr;

	return Back;
}

ESquadRow USquadComponent::GetRow(AHero* Hero) const
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

ESquadColumn USquadComponent::GetColumn(AHero* Hero) const
{
	for (const auto DropZone : DropZones)
	{
		if (DropZone->GetHero() == Hero)
		{
			return DropZone->Column;
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Hero %s not from current squad"), *Hero->GetName());
	return {};
}

AHero* USquadComponent::GetLeader()
{
	if (Leader == nullptr)
	{
		Leader = GetCenterDropZone()->GetHero();
	}
	return Leader;
}

UObject* USquadComponent::GetPlayerOwner() const
{
	return nullptr;
}

ADropZone* USquadComponent::GetDropZone(ESquadRow row, ESquadColumn column) const
{
	for (const auto DropZone : DropZones)
	{
		if (static_cast<int>(DropZone->Row) == static_cast<int>(row) &&
			static_cast<int>(DropZone->Column) == static_cast<int>(column))
		{
			return DropZone;
		}
	}

	return nullptr;
}

AHero* USquadComponent::FirstHeroInArray(TArray<AHero*> Heroes) const
{
	for (const auto Hero : Heroes)
	{
		if (Hero != nullptr)
		{
			return Hero;
		}
	}
	return nullptr;
}

ADropZone* USquadComponent::GetCenterDropZone()
{
	return GetDropZone(ESquadRow::Flank, ESquadColumn::Mid);
}

void USquadComponent::AddSquadEffect(FSquadEffect SquadEffect)
{
	SquadEffects.Add(SquadEffect);
	for (const auto DropZone : DropZones)
	{
		const AHero* Hero = DropZone->GetHero();
		if (!Hero)
			continue;
		UAbilitySystemComponent* LeaderASC = GetLeader()->GetAbilitySystemComponent();
		UAbilitySystemComponent* TargetASC = Hero->GetAbilitySystemComponent();
		
		LeaderASC->ApplyGameplayEffectSpecToTarget(*SquadEffect.EffectSpecHandle.Data, TargetASC);
	}
}

//TODO: Test
void USquadComponent::RemoveSquadEffect(TSubclassOf<UGameplayAbility> SourceAbility)
{
	TArray<const UGameplayEffect*> ToRemove;
	for (auto SquadEffect : SquadEffects)
	{
		if (SquadEffect.SourceAbility == SourceAbility)
		{
			ToRemove.Add(SquadEffect.EffectSpecHandle.Data->Def.Get());
			SquadEffects.Remove(SquadEffect);
		}
	}

	if (ToRemove.Num() <= 0)
		return;

	SquadEffects.RemoveAll([&ToRemove](const FSquadEffect& SquadEffect)
	{
		return ToRemove.Contains(SquadEffect.EffectSpecHandle.Data->Def.Get());
	});

	for (const auto DropZone : DropZones)
	{
		const AHero* Hero = DropZone->GetHero();
		if (!Hero)
			continue;
		UAbilitySystemComponent* ASC = Hero->GetAbilitySystemComponent();
		TArray<FActiveGameplayEffectHandle> ActiveGameplayEffectHandles = ASC->GetActiveEffects({});
		for (const auto RemoveEffectDef : ToRemove)
		{
			for (const auto EffectHandle : ActiveGameplayEffectHandles)
			{
				const UGameplayEffect* EffectDef = ASC->GetActiveGameplayEffect(EffectHandle)->Spec.Def;
				if (EffectDef == RemoveEffectDef)
				{
					ASC->RemoveActiveGameplayEffect(EffectHandle);
				}
			}
		}
	}
}

void USquadComponent::RemoveDropZoneEffect(TSubclassOf<UGameplayAbility> SourceAbility)
{
	for (auto DropZone : DropZones)
	{
		DropZone->RemoveZoneEffect(SourceAbility);
	}
}

TArray<ADropZone*> USquadComponent::GetDropZoneInRow(int RowNumber)
{
	TArray<ADropZone*> Result;
	for (auto DropZone : DropZones)
	{
		if (static_cast<int>(DropZone->Row) == RowNumber)
		{
			Result.Add(DropZone);
		}
	}
	return Result;
}

void USquadComponent::AddSquadAbility(FSquadAbility SquadAbility, bool activate)
{
	SquadAbilities.Add(SquadAbility);
	for (const auto DropZone : DropZones)
	{
		const AHero* Hero = DropZone->GetHero();
		if (!Hero)
			continue;
		UAbilitySystemComponent* TargetASC = Hero->GetAbilitySystemComponent();
		if (activate)
		{
			const FGameplayAbilitySpecHandle AbilitySpec = TargetASC->GiveAbility(
				SquadAbility.Ability.GetDefaultObject());
			TargetASC->TryActivateAbility(AbilitySpec);
		}
		else
		{
			TargetASC->GiveAbility(SquadAbility.Ability.GetDefaultObject());
		}
	}
}

void USquadComponent::RemoveSquadAbility(TSubclassOf<UGameplayAbility> SourceAbility)
{
	TArray<TSubclassOf<UGameplayAbility>> ToRemove;
	for (auto SquadAbility : SquadAbilities)
	{
		if (SquadAbility.SourceAbility == SourceAbility)
		{
			ToRemove.Add(SquadAbility.Ability);
		}
	}

	if (ToRemove.Num() <= 0)
		return;

	SquadAbilities.RemoveAll([&ToRemove](const FSquadAbility SquadAbility)
	{
		return ToRemove.Contains(SquadAbility.Ability);
	});

	for (const auto DropZone : DropZones)
	{
		const AHero* Hero = DropZone->GetHero();
		if (!Hero)
			continue;

		UAbilitySystemComponent* ASC = Hero->GetAbilitySystemComponent();
		TArray<FGameplayAbilitySpec> Abilities = ASC->GetActivatableAbilities();
		for (auto RemoveAbilityClass : ToRemove)
		{
			for (auto AbilitySpec : Abilities)
			{
				if (AbilitySpec.Ability.GetClass() == RemoveAbilityClass)
					ASC->ClearAbility(AbilitySpec.Handle);
			}
		}
	}
}

TArray<AHero*> USquadComponent::GetFirstHeroesInColumns() const
{
	TArray<AHero*> Result;

	const auto TopLine = GetHeroesInColumn(ESquadColumn::Top);
	const auto MiddleLine = GetHeroesInColumn(ESquadColumn::Mid);
	const auto BottomLine = GetHeroesInColumn(ESquadColumn::Bottom);

	AHero* Hero = nullptr;
	if (Hero = FirstHeroInArray(TopLine); Hero != nullptr)
		Result.Add(Hero);
	if (Hero = FirstHeroInArray(MiddleLine); Hero != nullptr)
		Result.Add(Hero);
	if (Hero = FirstHeroInArray(BottomLine); Hero != nullptr)
		Result.Add(Hero);

	return Result;
}

TArray<AHero*> USquadComponent::GetForwardHeroes(AHero* Hero) const
{
	ADropZone* HeroDropZone = GetDropZoneByHero(Hero);
	if (HeroDropZone->Row == ESquadRow::Vanguard)
		return {};
	TArray<AHero*> Result;
	switch (HeroDropZone->Row)
	{
	case ESquadRow::Flank:
		{
			AHero* VanguardHero = GetHero(ESquadRow::Vanguard, HeroDropZone->Column);
			if (VanguardHero != nullptr)
				Result.Add(VanguardHero);
			break;
		}
	case ESquadRow::Back:
		{
			AHero* VanguardHero = GetHero(ESquadRow::Vanguard, HeroDropZone->Column);
			if (VanguardHero != nullptr)
				Result.Add(VanguardHero);

			AHero* FlankHero = GetHero(ESquadRow::Flank, HeroDropZone->Column);
			if (FlankHero != nullptr)
				Result.Add(FlankHero);
			break;
		}
	}

	return Result;
}

ADropZone* USquadComponent::GetDropZoneByHero(AHero* Hero) const
{
	for (const auto DropZone : DropZones)
	{
		if (const auto TempHero = DropZone->GetHero(); TempHero != nullptr && TempHero == Hero)
		{
			return DropZone;
		}
	}

	return nullptr;
}


void USquadComponent::OnSetHero(AHero* NewHero)
{
	UAbilitySystemComponent* TargetASC = NewHero->GetAbilitySystemComponent();
	for (auto SquadEffect : SquadEffects)
	{
		TargetASC->ApplyGameplayEffectSpecToSelf(*SquadEffect.EffectSpecHandle.Data);
	}
	for (auto SquadAbility : SquadAbilities)
	{
		TargetASC->GiveAbility(SquadAbility.Ability.GetDefaultObject());
	}
}

AHero* USquadComponent::GetHero(ESquadRow Row, ESquadColumn Column) const
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
