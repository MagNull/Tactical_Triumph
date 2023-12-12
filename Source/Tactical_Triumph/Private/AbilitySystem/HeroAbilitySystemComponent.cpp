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

void UHeroAbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
                                                  FActiveGameplayEffectHandle ActiveEffectHandle) const
{
	if(EffectSpec.DynamicGrantedTags.Num() == 0)
		return;
	
	ASC->ClearAllAbilities();
	for (auto TagAbilityPair : TagToAbilityMap)
	{
		if (ASC->HasAnyMatchingGameplayTags(TagAbilityPair.Key.GetSingleTagContainer()))
		{
			UHeroGameplayAbility* Ability = TagAbilityPair.Value.GetDefaultObject();
			if (Ability->AbilityTags.HasAny(SpellTag.GetSingleTagContainer()))
			{
				ASC->GiveAbility(Ability);
			}
			else
			{
				FGameplayAbilitySpecHandle AbilitySpec = ASC->GiveAbility(Ability);
				ASC->TryActivateAbility(AbilitySpec);
			}
		}
	}
}
