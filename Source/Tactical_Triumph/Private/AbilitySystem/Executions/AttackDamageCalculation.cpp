
#include "AbilitySystem/Executions/AttackDamageCalculation.h"

#include "AbilitySystem/HeroAttributeSet.h"

struct FInflictDamageStatics
{
	FGameplayEffectAttributeCaptureDefinition Attack;
	FGameplayEffectAttributeCaptureDefinition DamageReduction;

	FInflictDamageStatics()
	{
		Attack = FGameplayEffectAttributeCaptureDefinition(UHeroAttributeSet::GetAttackAttribute(),
		                                                   EGameplayEffectAttributeCaptureSource::Source, false);

		DamageReduction = FGameplayEffectAttributeCaptureDefinition(
			UHeroAttributeSet::GetAttackDamageReductionAttribute(), EGameplayEffectAttributeCaptureSource::Target,
			false);
	}
};

static FInflictDamageStatics& AttackDamageStatics()
{
	static FInflictDamageStatics Statics;
	return Statics;
}

UAttackDamageCalculation::UAttackDamageCalculation()
{
}

void UAttackDamageCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                      FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const AHero* Source = Cast<AHero>(ExecutionParams.GetSourceAbilitySystemComponent()->GetOwner());
	const AHero* Target = Cast<AHero>(ExecutionParams.GetTargetAbilitySystemComponent()->GetOwner());

	const float Damage = Source->GetAttack();
	const float AttackDamageReduction = Target->GetDamageReduction();

	const float ResultDamage = FMathf::Clamp(Damage - AttackDamageReduction, 0, 1000);
	
	if (ResultDamage > 0.0f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(UHeroAttributeSet::GetPresentDamageAttribute(), EGameplayModOp::Additive,
			                               ResultDamage));
		OutExecutionOutput.MarkConditionalGameplayEffectsToTrigger();
	}
}
