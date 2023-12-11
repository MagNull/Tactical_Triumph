// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor_Trace.h"
#include "HeroAbilityTargeting.generated.h"

class AHero;

UCLASS()
class TACTICAL_TRIUMPH_API AHeroAbilityTargeting : public AGameplayAbilityTargetActor_Trace
{
	GENERATED_BODY()
public:
	virtual FHitResult PerformTrace(AActor* InSourceActor) override;
	virtual bool ShouldProduceTargetData() const override;
	virtual void ConfirmTargetingAndContinue() override;
protected:
	FGameplayAbilityTargetDataHandle MakeTargetData(FHitResult hitResult);

	AHero* LastTargetHero;
};
