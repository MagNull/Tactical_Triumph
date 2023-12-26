// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectComponent.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "SendEventGameplayEffectComponent.generated.h"


/**
 * 
 */
UCLASS()
class TACTICAL_TRIUMPH_API USendEventGameplayEffectComponent : public UGameplayEffectComponent
{
	GENERATED_BODY()

public:
	virtual void OnGameplayEffectApplied(FActiveGameplayEffectsContainer& ActiveGEContainer,
	                                     FGameplayEffectSpec& GESpec, FPredictionKey& PredictionKey) const override;
	UPROPERTY(EditAnywhere, Category = "Send To Target")
	FGameplayTag TargetEventTag;
	
	UPROPERTY(EditAnywhere, Category = "Send To Instigator")
	FGameplayTag InstigatorEventTag;
};
