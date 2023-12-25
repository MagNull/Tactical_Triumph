#include "Squad/SquadComponent.h"

#include "DragAndDrop/DropZone.h"

USquadComponent::USquadComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USquadComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto DropZone : DropZones)
	{
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

void USquadComponent::GetNeighbours(AHero* OriginHero, AHero*& OutForward, AHero*& OutBack) const
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

ADropZone* USquadComponent::GetCenterDropZone()
{
	return GetDropZone(ESquadRow::Flank, ESquadColumn::Mid);
}

void USquadComponent::AddSquadEffect(TSubclassOf<UGameplayEffect> Effect)
{
	SquadEffects.Add(Effect);
	for (const auto DropZone : DropZones)
	{
		UAbilitySystemComponent* TargetASC = DropZone->GetHero()->GetAbilitySystemComponent();
		TargetASC->ApplyGameplayEffectToSelf(Effect.GetDefaultObject(), 0, TargetASC->MakeEffectContext());
	}
}

void USquadComponent::AddSquadAbility(TSubclassOf<UHeroGameplayAbility> Ability, bool activate)
{
	// 	SquadAbilities.Add(Ability);
	// 	for (const auto DropZone : DropZones)
	// 	{
	// 		UAbilitySystemComponent* TargetASC = DropZone->GetHero()->GetAbilitySystemComponent();
	// 		if (activate)
	// 		{
	// 			const FGameplayAbilitySpecHandle AbilitySpec = TargetASC->GiveAbility(Ability.GetDefaultObject());
	// 			TargetASC->TryActivateAbility(AbilitySpec);
	// 		}
	// 		else
	// 		{
	// 			TargetASC->GiveAbility(Ability.GetDefaultObject());
	// 		}
	// 	}
}

void USquadComponent::OnSetHero(AHero* NewHero)
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
