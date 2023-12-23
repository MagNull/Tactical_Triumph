#include "Tactical_Triumph/Public/AbilitySystem/HeroGameplayAbility.h"

UHeroGameplayAbility::UHeroGameplayAbility()
{
}

void UHeroGameplayAbility::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);
	OnAbilityRemoved();
}
