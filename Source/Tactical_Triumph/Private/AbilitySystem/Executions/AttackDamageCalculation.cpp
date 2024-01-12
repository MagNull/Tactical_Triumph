#include "AbilitySystem/Executions/AttackDamageCalculation.h"
#include "AbilitySystem/HeroAttributeSet.h"

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
