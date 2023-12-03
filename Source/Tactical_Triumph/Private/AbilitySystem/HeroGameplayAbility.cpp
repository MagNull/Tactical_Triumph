#include "Tactical_Triumph/Public/AbilitySystem/HeroGameplayAbility.h"

UHeroGameplayAbility::UHeroGameplayAbility()
{
}

void UHeroGameplayAbility::AddTrigger(FAbilityTriggerData TriggerData)
{
	AbilityTriggers.Emplace(TriggerData);
}
