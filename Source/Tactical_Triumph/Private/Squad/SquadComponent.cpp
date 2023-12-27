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

void USquadComponent::GetNeighbours(AHero* OriginHero, AHero*& OutForward, AHero*& OutBack) const
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
		OutForward = DropZone->GetHero();
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
		OutBack = DropZone->GetHero();
	}
}

AHero* USquadComponent::GetForwardNeighbour(AHero* OriginHero)
{
	AHero *Forward = nullptr, *Back = nullptr;
	GetNeighbours(OriginHero, Forward, Back);
	UE_LOG(LogTemp, Display, TEXT("%hd"), Forward == nullptr)
	if (Forward == nullptr)
		return nullptr;

	return Forward;
}

AHero* USquadComponent::GetBackNeighbour(AHero* OriginHero)
{
	AHero *Forward = nullptr, *Back = nullptr;
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

AHero* USquadComponent::FirstHeroInArray(TArray<AHero*> Heroes)
{
	for(const auto Hero : Heroes)
	{
		if(Hero != nullptr)
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

TArray<AHero*> USquadComponent::GetFirstHeroesInColumns()
{
	TArray<AHero*> Result;

	const auto TopLine = GetHeroesInColumn(ESquadColumn::Top);
	const auto MiddleLine = GetHeroesInColumn(ESquadColumn::Mid);
	const auto BottomLine = GetHeroesInColumn(ESquadColumn::Bottom);

	AHero* Hero = nullptr;
	if(Hero = FirstHeroInArray(TopLine); Hero != nullptr)
		Result.Add(Hero);
	if(Hero = FirstHeroInArray(MiddleLine); Hero != nullptr)
		Result.Add(Hero);
	if(Hero = FirstHeroInArray(BottomLine); Hero != nullptr)
		Result.Add(Hero);
	
	return Result;
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
