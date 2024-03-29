// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor_Trace.h"
#include "HeroAbilityTargeting.generated.h"

class AHero;

UENUM(BlueprintType)
enum class ESelectionType : uint8
{
	Hero,
	Column,
	Row,
	Cell
};

UCLASS()
class TACTICAL_TRIUMPH_API AHeroAbilityTargeting : public AGameplayAbilityTargetActor_Trace
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void WrongTargetWarning();

	virtual bool IsConfirmTargetingAllowed() override;
	
	virtual FHitResult PerformTrace(AActor* InSourceActor) override;
	virtual bool ShouldProduceTargetData() const override;
	virtual void ConfirmTargetingAndContinue() override;

	virtual void StartTargeting(UGameplayAbility* Ability) override;
	virtual void ConfirmTargeting() override;
	virtual void CancelTargeting() override;

protected:
	FGameplayAbilityTargetDataHandle MakeTargetData(const FHitResult& hitResult) const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Selection")
	ESelectionType SelectionType;
};
