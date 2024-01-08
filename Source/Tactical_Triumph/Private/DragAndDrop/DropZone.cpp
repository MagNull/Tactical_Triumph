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
	for (auto ZoneEffect : ZoneEffects)
	{
		CurrentHero->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*ZoneEffect.Data.Get());
	}
}

bool ADropZone::IsCenter()
{
	return Column == ESquadColumn::Mid && Row == ESquadRow::Flank;
}

APlayerPawn* ADropZone::GetPlayerOwner()
{
	return PlayerOwnerPawn;
}

void ADropZone::AddZoneEffect(const FGameplayEffectSpecHandle EffectHandle)
{
	ZoneEffects.Add(EffectHandle);
	if (CurrentHero)
	{
		CurrentHero->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*EffectHandle.Data.Get());
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
	for (auto ZoneEffect : ZoneEffects)
	{
		const FActiveGameplayEffect* TargetActiveEffect = nullptr;
		for (auto ActiveEffectHandle : ActiveEffectHandles)
		{
			const FActiveGameplayEffect* Effect = AbilitySystemComponent->GetActiveGameplayEffect(ActiveEffectHandle);
			if (AbilitySystemComponent->GetActiveGameplayEffect(ActiveEffectHandle)->Spec.Def == ZoneEffect.Data->Def)
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
	if(CurrentHero == nullptr)
		return;
	
	RemoveGrantedTag(CurrentHero);
	RemoveZoneEffectsFromHero(CurrentHero);
	CurrentHero = nullptr;
}
