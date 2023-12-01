#include "Tactical_Triumph/Public/AbilitySystem/Hero.h"
#include "AbilitySystemComponent.h"
#include "Tactical_Triumph/Public/AbilitySystem/HeroAttributeSet.h"
#include "Tactical_Triumph/Public/AbilitySystem/HeroGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"

AHero::AHero()
{
	bAbilitiesIsInitialized = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("GAS Componens"));
	AbilitySystemComponent->SetIsReplicated(true);

	Attributes = CreateDefaultSubobject<UHeroAttributeSet>(TEXT("Attributes"));
}

void AHero::BeginPlay()
{
	Super::BeginPlay();

	AddStartupAbilities();
}

void AHero::AddStartupAbilities()
{
	check(AbilitySystemComponent)
	if (bAbilitiesIsInitialized)
		return;

	//Granting abilities
	for (TPair<FGameplayTag, TSubclassOf<UHeroGameplayAbility>>& Ability : Abilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec{
			Ability.Value, 1, static_cast<int32>(Ability.Value.GetDefaultObject()->AbilityInputID), this
		});
	}

	//Granting passives effect
	for (const auto StartupEffect : StartupEffects)
	{
		FGameplayEffectContextHandle effectContext = AbilitySystemComponent->MakeEffectContext();
		effectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle effectHandle =
			AbilitySystemComponent->MakeOutgoingSpec(StartupEffect, 1, effectContext);

		if (effectHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
				*effectHandle.Data.Get(), AbilitySystemComponent);
		}
	}

	bAbilitiesIsInitialized = true;
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

void AHero::HandleDamage(float DamageAmount, const FGameplayTagContainer DamageTags,
                         UAbilitySystemComponent* DamageInstigator, UAbilitySystemComponent* Target)
{
	OnDamaged(DamageAmount, DamageTags,
	          DamageInstigator, Target);
}

void AHero::HandleHealthChanged(float deltaValue, const FGameplayTagContainer& eventTags)
{
	OnHealthChanged(deltaValue, eventTags);
}
