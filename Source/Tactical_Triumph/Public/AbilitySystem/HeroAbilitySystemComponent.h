#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/HeroGameplayAbility.h"
#include "HeroAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class TACTICAL_TRIUMPH_API UHeroAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetAbilitySquadLineMap(TMap<FGameplayTag, TSubclassOf<UHeroGameplayAbility>> map);
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

private:
	void OnEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
	                     FActiveGameplayEffectHandle ActiveEffectHandle) const;

	UPROPERTY(EditAnywhere)
	FGameplayTag SpellTag;

	TMap<FGameplayTag, TSubclassOf<UHeroGameplayAbility>> TagToAbilityMap;
	FDelegateHandle EffectAppliedHandle;
};
