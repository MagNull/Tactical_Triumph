#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetDataFilter.h"
#include "SelectedTargetsFilter.generated.h"


USTRUCT()
struct TACTICAL_TRIUMPH_API FSelectedTargetsFilter : public FGameplayTargetDataFilter
{	
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Filter)
	TArray<AActor*> SelectedActors;
	
	virtual bool FilterPassesForActor(const AActor* ActorToBeFiltered) const override;
};
