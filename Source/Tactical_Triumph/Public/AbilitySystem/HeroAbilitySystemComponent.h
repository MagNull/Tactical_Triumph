#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/HeroGameplayAbility.h"
#include "HeroAbilitySystemComponent.generated.h"

UCLASS()
class TACTICAL_TRIUMPH_API UHeroAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	DECLARE_DELEGATE(FBeforeAllAbilitiesClearing)

public:
	UFUNCTION(BlueprintCallable)
	void SetAbilitySquadLineMap(TMap<FGameplayTag, TSubclassOf<UHeroGameplayAbility>> map);

	UFUNCTION(BlueprintCallable)
	bool CanActivateAbilityWithTag(FGameplayTagContainer TagContainer);
	
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	TArray<FActiveGameplayEffectHandle> GetActiveGameplayEffectsByAbility(
		const UGameplayAbility* InstigatorAbility) const;

private:
	void OnEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
						 FActiveGameplayEffectHandle ActiveEffectHandle);
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer ActivableAbilityTags;
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer PositionTags;

	TMap<FGameplayTag, TSubclassOf<UHeroGameplayAbility>> TagToAbilityMap;
	FDelegateHandle EffectAppliedHandle;
	FBeforeAllAbilitiesClearing OnBeforeAllAbilitiesClearingDelegate;
};
