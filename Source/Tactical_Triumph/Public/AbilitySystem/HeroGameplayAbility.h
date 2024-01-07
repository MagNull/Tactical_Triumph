#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "HeroGameplayAbility.generated.h"


struct FSquadEffect;
struct FSquadAbility;
class UHeroAbilitySystemComponent;

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None,
	Cancel,
	Confirm,
};

UCLASS()
class TACTICAL_TRIUMPH_API UHeroGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	friend UHeroAbilitySystemComponent;

public:
	UHeroGameplayAbility();

	void RemoveCausedEffects(AActor* OwnerActor) const;
	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                       FGameplayTagContainer* OptionalRelevantTags) const override;

	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool CommitAbilityCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                               const FGameplayAbilityActivationInfo ActivationInfo,
	                               FGameplayTagContainer* OptionalRelevantTags) override;

protected:
	UFUNCTION(BlueprintCallable)
	FSquadAbility GetSquadAbility(TSubclassOf<UGameplayAbility> Ability) const;

	UFUNCTION(BlueprintCallable)
	FSquadEffect GetSquadEffect(FGameplayEffectSpecHandle SpecHandle) const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnAbilityRemoved();
};
