#include "AbilitySystem/PlayerAttributeSet.h"

#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/Hero.h"
#include "Net/UnrealNetwork.h"
#include "Pawn/PlayerPawn.h"

void UPlayerAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, ActionPoints, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, ActionPointsRestoration, COND_None, REPNOTIFY_Always);
}

void UPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetActionPointsAttribute())
	{
		const float ClampedActionPointsCount = FMath::Clamp(GetActionPoints(), 0, 1000);
		SetActionPoints(ClampedActionPointsCount);
		
		APlayerPawn* PlayerPawn = Cast<APlayerPawn>(GetOwningAbilitySystemComponent()->GetOwner());
		if(PlayerPawn)
		{
			PlayerPawn->HandleActionPointsChanged();
		}
	}
}

void UPlayerAttributeSet::OnRep_ActionPoints(const FGameplayAttributeData oldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, ActionPoints, oldData);
}

void UPlayerAttributeSet::OnRep_ActionPointsRestoration(const FGameplayAttributeData oldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, ActionPointsRestoration, oldData);
}
