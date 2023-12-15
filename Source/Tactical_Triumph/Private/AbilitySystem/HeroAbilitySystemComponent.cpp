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
	FGameplayTagContainer GrantedTags;
	EffectSpec.GetAllGrantedTags(GrantedTags);
	if (GrantedTags.Num() == 0)
		return;
	
	
	for (auto TagAbilityPair : TagToAbilityMap)
	{
		UHeroGameplayAbility* Ability = TagAbilityPair.Value.GetDefaultObject();

		//Clear all this ability duplicates
		TArray<FGameplayAbilitySpecHandle> Abilities;
		ASC->GetAllAbilities(Abilities);
		for (auto ASH : Abilities)
		{
			const UGameplayAbility* OtherAbility = ASC->FindAbilitySpecFromHandle(ASH)->Ability;
			if(OtherAbility == Ability)
			{
				ASC->ClearAbility(ASH);
			}
		}
		
		if (ASC->HasAnyMatchingGameplayTags(TagAbilityPair.Key.GetSingleTagContainer()))
		{
			if (Ability->AbilityTags.HasAny(NotActivableAbilityTags))
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
