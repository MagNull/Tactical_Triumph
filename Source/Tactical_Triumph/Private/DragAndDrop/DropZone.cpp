#include "DragAndDrop/DropZone.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Hero.h"
#include "Kismet/GameplayStatics.h"

ADropZone::ADropZone()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComponent);

	HeroSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Hero Spawn Point"));
	HeroSpawnPoint->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

int ADropZone::GetRowInt() const
{
	return static_cast<int>(Row);
}

int ADropZone::GetColumnInt() const
{
	return static_cast<int>(Column);
}

bool ADropZone::IsOccupied() const
{
	return CurrentHero != nullptr;
}

AHero* ADropZone::GetHero() const
{
	return CurrentHero;
}

void ADropZone::SetHero(AHero* NewHero)
{
	if (NewHero == nullptr)
		return;

	CurrentHero = NewHero;
	CurrentHero->SetActorLocation(HeroSpawnPoint->GetComponentLocation());
	OnSetHero.Broadcast(NewHero);

	ApplyGrantedTag(CurrentHero);
	for (auto ZoneEffect : ZoneEffectPairs)
	{
		CurrentHero->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*ZoneEffect.Key.Data.Get());
	}
}

bool ADropZone::IsCenter()
{
	return Column == ESquadColumn::Mid && Row == ESquadRow::Flank;
}

void ADropZone::AddZoneEffect(const FGameplayEffectSpecHandle EffectHandle, UGameplayAbility* SourceAbility)
{
	ZoneEffectPairs.Add({EffectHandle, SourceAbility->GetClass()});
	if (CurrentHero)
	{
		CurrentHero->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*EffectHandle.Data.Get());
	}
}

void ADropZone::RemoveZoneEffect(TSubclassOf<UGameplayAbility> Ability)
{
	TArray<TTuple<FGameplayEffectSpecHandle, UClass*>> ToRemove;
	for (auto ZoneEffect : ZoneEffectPairs)
	{
		if (ZoneEffect.Value == Ability)
			ToRemove.Add(ZoneEffect);
	}
	for (auto Tuple : ToRemove)
	{
		ZoneEffectPairs.Remove(Tuple);
	}
}

void ADropZone::ApplyGrantedTag(AHero* Hero)
{
	UAbilitySystemComponent* ASC = Hero->GetAbilitySystemComponent();
	FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(InfiniteEffect, 1, ASC->MakeEffectContext());
	EffectSpecHandle.Data->DynamicGrantedTags.AddTag(GrantedTag);
	ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
}

void ADropZone::RemoveGrantedTag(AHero* Hero)
{
	UE_LOG(LogTemp, Display, TEXT("Start Removing"));
	if (!Hero)
	{
		return;
	}

	UAbilitySystemComponent* ASC = Hero->GetAbilitySystemComponent();
	const TArray<FActiveGameplayEffectHandle> EffectsContainer = ASC->GetActiveEffects({});
	FActiveGameplayEffectHandle TargetEffectHandle;
	for (auto EffectHandle : EffectsContainer)
	{
		const FActiveGameplayEffect* Effect = ASC->GetActiveGameplayEffect(EffectHandle);

		if (Effect->Spec.DynamicGrantedTags.HasTag(GrantedTag))
			TargetEffectHandle = EffectHandle;
	}

	if (!TargetEffectHandle.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Hero doesnt have tag effect, granted by this zone"));
		return;
	}

	ASC->RemoveActiveGameplayEffect(TargetEffectHandle);
}

void ADropZone::RemoveZoneEffectsFromHero(AHero* Hero)
{
	UAbilitySystemComponent* AbilitySystemComponent = Hero->GetAbilitySystemComponent();
	TArray<FActiveGameplayEffectHandle> ActiveEffectHandles = AbilitySystemComponent->GetActiveGameplayEffects().
		GetActiveEffects({});
	for (auto ZoneEffect : ZoneEffectPairs)
	{
		const FActiveGameplayEffect* TargetActiveEffect = nullptr;
		for (auto ActiveEffectHandle : ActiveEffectHandles)
		{
			const FActiveGameplayEffect* Effect = AbilitySystemComponent->GetActiveGameplayEffect(ActiveEffectHandle);
			if (AbilitySystemComponent->GetActiveGameplayEffect(ActiveEffectHandle)->Spec.Def ==
				ZoneEffect.Key.Data->Def)
			{
				TargetActiveEffect = Effect;
				break;
			}
		}
		if (TargetActiveEffect)
			AbilitySystemComponent->RemoveActiveGameplayEffect(TargetActiveEffect->Handle);
	}
}

void ADropZone::Clear()
{
	if (CurrentHero == nullptr)
		return;

	RemoveGrantedTag(CurrentHero);
	RemoveZoneEffectsFromHero(CurrentHero);
	CurrentHero = nullptr;
}
