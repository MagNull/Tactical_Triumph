// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "HeroGameplayAbility.generated.h"


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
public:
	UHeroGameplayAbility();

	void AddTrigger(FAbilityTriggerData TriggerData);
	void AddRequiredTag(const FGameplayTag& tag);
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	EAbilityInputID AbilityInputID;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	bool bIsSpell;
};
