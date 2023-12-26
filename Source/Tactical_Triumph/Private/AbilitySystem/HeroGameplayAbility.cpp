#include "Tactical_Triumph/Public/AbilitySystem/HeroGameplayAbility.h"

#include "BattleState.h"
#include "AbilitySystem/Hero.h"
#include "AbilitySystem/HeroAbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/PlayerPawn.h"
#include "Squad/SquadComponent.h"

UHeroGameplayAbility::UHeroGameplayAbility()
{
}

void UHeroGameplayAbility::RemoveCausedEffects(AActor* OwnerActor) const
{
	TArray<AActor*> AllHeroes;
	UGameplayStatics::GetAllActorsOfClass(OwnerActor->GetWorld(), AHero::StaticClass(), AllHeroes);
	for (const auto Actor : AllHeroes)
	{
		const AHero* Hero = Cast<AHero>(Actor);
		if (!Hero)
			continue;
		UHeroAbilitySystemComponent* HeroASC = Cast<UHeroAbilitySystemComponent>(Hero->GetAbilitySystemComponent());
	
		TArray<FActiveGameplayEffectHandle> EffectsToRemove = HeroASC->GetActiveGameplayEffectsByAbility(this);
		for (const auto ToRemove : EffectsToRemove)
		{
			HeroASC->RemoveActiveGameplayEffect(ToRemove);
		}
	}
}

void UHeroGameplayAbility::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	OnAbilityRemoved();
	RemoveCausedEffects(ActorInfo->OwnerActor.Get());
	USquadComponent* Squad = UBattleState::GetActivePlayer()->GetComponentByClass<USquadComponent>();
	if(Squad == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s get Squad is null"), *GetName());
		return;
	}
	Squad->RemoveSquadAbility(GetClass());
	Squad->RemoveSquadEffect(GetClass());
}

FSquadAbility UHeroGameplayAbility::GetSquadAbility(TSubclassOf<UGameplayAbility> Ability) const
{
	return FSquadAbility{Ability, GetClass()};
}

FSquadEffect UHeroGameplayAbility::GetSquadEffect(FGameplayEffectSpecHandle SpecHandle) const
{
	return FSquadEffect{SpecHandle, GetClass()};
}
