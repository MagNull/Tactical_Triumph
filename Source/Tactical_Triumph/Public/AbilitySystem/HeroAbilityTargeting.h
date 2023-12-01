// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor_Trace.h"
#include "HeroAbilityTargeting.generated.h"


/**
 * 
 */
UCLASS()
class TACTICAL_TRIUMPH_API AHeroAbilityTargeting : public AGameplayAbilityTargetActor_Trace
{
	GENERATED_BODY()

	virtual FHitResult PerformTrace(AActor* InSourceActor) override;
	virtual bool ShouldProduceTargetData() const override;
};
