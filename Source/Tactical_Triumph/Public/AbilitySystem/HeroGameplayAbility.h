// Fill out your copyright notice in the Description page of Project Settings.

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

	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

protected:
	UFUNCTION(BlueprintCallable)
	FSquadAbility GetSquadAbility(TSubclassOf<UGameplayAbility> Ability) const;
	
	UFUNCTION(BlueprintCallable)
	FSquadEffect GetSquadEffect(FGameplayEffectSpecHandle SpecHandle) const;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnAbilityRemoved();
};
