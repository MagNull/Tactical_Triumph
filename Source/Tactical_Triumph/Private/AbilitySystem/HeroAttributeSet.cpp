#include "Tactical_Triumph/Public/AbilitySystem/HeroAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Tactical_Triumph/Public/AbilitySystem/Hero.h"

#include "Net/UnrealNetwork.h"


UHeroAttributeSet::UHeroAttributeSet()
{
}

void UHeroAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, Attack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, PresentDamage, COND_None, REPNOTIFY_Always);
}

void UHeroAttributeSet::BreakEffectData(const FGameplayEffectModCallbackData& Data, FGameplayTagContainer& tagContainer,
                                        float& deltaValue, UAbilitySystemComponent* instigator, AHero*& target)
{
	FGameplayEffectContextHandle context = Data.EffectSpec.GetContext();
	instigator = context.GetOriginalInstigatorAbilitySystemComponent();
	tagContainer = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	deltaValue = 0;

	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Additive)
	{
		deltaValue = Data.EvaluatedData.Magnitude;
	}

	target = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		AActor* targetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		target = Cast<AHero>(targetActor);
	}
}

void UHeroAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	UE_LOG(LogTemp, Display, TEXT("Trigger"));
	FGameplayTagContainer TagContainer;
	float DeltaValue;
	UAbilitySystemComponent* Instigator = nullptr;
	AHero* Target;
	BreakEffectData(Data, TagContainer, DeltaValue, Instigator, Target);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		const float NewHealth = FMath::Clamp(GetHealth(), 0, GetMaxHealth());
		DeltaValue = GetHealth() - NewHealth;
		SetHealth(NewHealth);
		if (Target)
		{
			Target->HandleHealthChanged(DeltaValue, TagContainer);
		}
	}

	if (Data.EvaluatedData.Attribute == GetPresentDamageAttribute())
	{
		UE_LOG(LogTemp, Display, TEXT("Damaged"));
		if (Target)
		{
			Target->HandleDamageChanged(DeltaValue, TagContainer, Instigator, Target->GetAbilitySystemComponent());
		}
	}
}

void UHeroAttributeSet::OnRep_Health(const FGameplayAttributeData oldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, Health, oldData);
}

void UHeroAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData oldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, MaxHealth, oldData);
}

void UHeroAttributeSet::OnRep_Attack(const FGameplayAttributeData oldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, Attack, oldData);
}

void UHeroAttributeSet::OnRep_PresentDamage(const FGameplayAttributeData oldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, PresentDamage, oldData);
}
