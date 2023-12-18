#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "AttackDamageCalculation.generated.h"


UCLASS()
class TACTICAL_TRIUMPH_API UAttackDamageCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UAttackDamageCalculation();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
