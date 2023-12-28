#include "AbilitySystem/HeroAbilitySystemComponent.h"

void UHeroAbilitySystemComponent::SetAbilitySquadLineMap(TMap<FGameplayTag, TSubclassOf<UHeroGameplayAbility>> map)
{
	TagToAbilityMap = map;
}

void UHeroAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
	EffectAppliedHandle = OnGameplayEffectAppliedDelegateToSelf.AddUObject(
		this, &UHeroAbilitySystemComponent::OnEffectApplied);
}

void UHeroAbilitySystemComponent::BeginDestroy()
{
	Super::BeginDestroy();
	OnGameplayEffectAppliedDelegateToSelf.Remove(EffectAppliedHandle);
}

TArray<FActiveGameplayEffectHandle> UHeroAbilitySystemComponent::GetActiveGameplayEffectsByAbility(
	const UGameplayAbility* InstigatorAbility) const
{
	TArray<FActiveGameplayEffectHandle> Result;
	const TArray<FActiveGameplayEffectHandle> EffectsContainer = GetActiveEffects({});
	for (auto EffectSpecHandle : EffectsContainer)
	{
		FGameplayEffectContextHandle ContextHandle = GetActiveGameplayEffect(EffectSpecHandle)->Spec.GetContext();
		const UGameplayAbility* EffectInstigatorAbility = ContextHandle.GetAbility();
		if (EffectInstigatorAbility &&
			EffectInstigatorAbility->GetClass() == InstigatorAbility->GetClass())
		{
			Result.Add(EffectSpecHandle);
		}
	}
	return Result;
}

void UHeroAbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
                                                  FActiveGameplayEffectHandle ActiveEffectHandle)
{
	if (!EffectSpec.DynamicGrantedTags.HasAnyExact(PositionTags))
		return;

	for (auto TagAbilityPair : TagToAbilityMap)
	{
		UHeroGameplayAbility* Ability = TagAbilityPair.Value.GetDefaultObject();

		//Clear all this ability duplicates
		TArray<FGameplayAbilitySpec> Abilities = GetActivatableAbilities();
		for (auto AbilitySpec : Abilities)
		{
			if (AbilitySpec.Ability.GetClass() == Ability->GetClass())
			{
				ClearAbility(AbilitySpec.Handle);
			}
		}
		
		if (ASC->HasAnyMatchingGameplayTags(TagAbilityPair.Key.GetSingleTagContainer()))
		{
			if (Ability->AbilityTags.HasAny(ActivableAbilityTags))
			{
				FGameplayAbilitySpecHandle AbilitySpec = GiveAbility(Ability);
				TryActivateAbility(AbilitySpec);
			}
			else
			{
				GiveAbility(Ability);
			}
		}
	}
}
