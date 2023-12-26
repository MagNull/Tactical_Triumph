#include "Tactical_Triumph/Public/AbilitySystem/Hero.h"
#include "Tactical_Triumph/Public/AbilitySystem/HeroAbilitySystemComponent.h"
#include "AbilitySystemComponent.h"
#include "Tactical_Triumph/Public/AbilitySystem/HeroAttributeSet.h"

AHero::AHero()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));

	AbilitySystemComponent = CreateDefaultSubobject<UHeroAbilitySystemComponent>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);

	Attributes = CreateDefaultSubobject<UHeroAttributeSet>(TEXT("Attributes"));
}

UAbilitySystemComponent* AHero::GetAbilitySystemComponent() const
{
	return Cast<UAbilitySystemComponent>(AbilitySystemComponent);
}

float AHero::GetHealth() const
{
	return Attributes->GetHealth();
}

float AHero::GetAttack() const
{
	return Attributes->GetAttack();
}

float AHero::GetDamageReduction() const
{
	return Attributes->GetAttackDamageReduction();
}

float AHero::GetPresentDamage() const
{
	return Attributes->GetPresentDamage();
}

float AHero::GetMaxHealth() const
{
	return Attributes->GetMaxHealth();
}

void AHero::HandleDamageChanged(float DamageAmount, const FGameplayTagContainer DamageTags,
                                UAbilitySystemComponent* DamageInstigator, UAbilitySystemComponent* Target)
{
	OnDamageChanged(DamageAmount, DamageTags,
	                DamageInstigator, Target);
}

void AHero::HandleHealthChanged(float deltaValue, const FGameplayTagContainer& eventTags)
{
	OnHealthChanged(deltaValue, eventTags);
	if (GetHealth() <= 0)
	{
		Died();
	}
}

void AHero::HandleAttackChanged(float deltaValue, const FGameplayTagContainer& eventTags)
{
	OnAttackChanged(deltaValue, eventTags);
}
