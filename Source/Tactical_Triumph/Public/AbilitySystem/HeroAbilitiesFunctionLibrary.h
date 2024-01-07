#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetDataFilter.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HeroAbilitiesFunctionLibrary.generated.h"

struct FSelectedTargetsFilter;


UCLASS()
class TACTICAL_TRIUMPH_API UHeroAbilitiesFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FGameplayTargetDataFilterHandle MakeSelectedFilterHandle(
		FSelectedTargetsFilter Filter, AActor* FilterActor);
};
