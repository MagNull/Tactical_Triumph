// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectedTargetsFilter.h"

bool FSelectedTargetsFilter::FilterPassesForActor(const AActor* ActorToBeFiltered) const
{
	return SelectedActors.Contains(ActorToBeFiltered);
}
