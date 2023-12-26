#include "GameplayEffectComponents/SendEventGameplayEffectComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffect.h"

void USendEventGameplayEffectComponent::OnGameplayEffectApplied(FActiveGameplayEffectsContainer& ActiveGEContainer,
                                                                FGameplayEffectSpec& GESpec, FPredictionKey& PredictionKey) const
{
	Super::OnGameplayEffectApplied(ActiveGEContainer, GESpec, PredictionKey);
	AActor* Target = ActiveGEContainer.Owner->GetOwnerActor();
	AActor* Instigator = GESpec.GetContext().GetInstigator();
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Target, TargetEventTag, {});
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Instigator, InstigatorEventTag, {});
	
}
