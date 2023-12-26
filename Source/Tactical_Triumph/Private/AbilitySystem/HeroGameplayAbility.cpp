#include "Tactical_Triumph/Public/AbilitySystem/HeroGameplayAbility.h"

#include "AbilitySystem/Hero.h"
#include "AbilitySystem/HeroAbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Squad/Squad.h"

class USquad;

UHeroGameplayAbility::UHeroGameplayAbility()
{
}

void UHeroGameplayAbility::RemoveCausedEffects() const
{
	TArray<AActor*> AllHeroes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHero::StaticClass(), AllHeroes);
	for (const auto Actor : AllHeroes)
	{
		const AHero* Hero = Cast<AHero>(Actor);
		if (!Hero)
			continue;
		UHeroAbilitySystemComponent* ASC = Cast<UHeroAbilitySystemComponent>(Hero->GetAbilitySystemComponent());

		TArray<FActiveGameplayEffectHandle> EffectsToRemove = ASC->GetActiveGameplayEffectsByAbility(this);
		for (const auto ToRemove : EffectsToRemove)
		{
			ASC->RemoveActiveGameplayEffect(ToRemove);
		}
	}
}

void UHeroGameplayAbility::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	OnAbilityRemoved();
	RemoveCausedEffects();
	// auto pp = UGameplayStatics::GetPlayerPawn(ActorInfo->OwnerActor->GetWorld(), 0);
	// if()
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("World null"));
	// 	return;
	// }
	// USquad* Squad = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetComponentByClass<USquad>();
	// if(Squad == nullptr)
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("Squad null"));
	// 	return;
	// }
	// Squad->RemoveSquadAbility(GetClass());
	// Squad->RemoveSquadEffect(GetClass());
}

FSquadAbility UHeroGameplayAbility::GetSquadAbility(TSubclassOf<UGameplayAbility> Ability) const
{
	return FSquadAbility{Ability, GetClass()};
}

FSquadEffect UHeroGameplayAbility::GetSquadEffect(FGameplayEffectSpecHandle SpecHandle) const
{
	return FSquadEffect{SpecHandle, GetClass()};
}
