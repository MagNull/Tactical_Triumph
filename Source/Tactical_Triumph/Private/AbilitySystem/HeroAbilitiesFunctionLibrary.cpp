// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/HeroAbilitiesFunctionLibrary.h"

#include "SelectedTargetsFilter.h"

FGameplayTargetDataFilterHandle UHeroAbilitiesFunctionLibrary::MakeSelectedFilterHandle(FSelectedTargetsFilter Filter,
                                                                                        AActor* FilterActor)
{
	FGameplayTargetDataFilter* NewFilter = new FSelectedTargetsFilter(Filter);
	NewFilter->InitializeFilterContext(FilterActor);

	FGameplayTargetDataFilterHandle FilterHandle;
	FilterHandle.Filter = TSharedPtr<FGameplayTargetDataFilter>(NewFilter);
	return FilterHandle;
}

