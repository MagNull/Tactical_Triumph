// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DropZone.h"
#include "ISquad.h"
#include "AbilitySystem/Hero.h"
#include "AbilitySystem/SquadLines.h"
#include "Components/ActorComponent.h"
#include "Squad.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TACTICAL_TRIUMPH_API USquad : public UActorComponent, public ISquad
{
	GENERATED_BODY()

public:
	USquad();

	UFUNCTION(BlueprintCallable)
	virtual TArray<AHero*> GetHeroesInColumn(ESquadColumn Column) const override;

	UFUNCTION(BlueprintCallable)
	virtual void GetNeighbours(AHero* OriginHero, AHero* OutForward, AHero* OutBack) const override;

	UFUNCTION(BlueprintCallable)
	virtual ESquadRow GetRow(AHero* Hero) const override;

	UFUNCTION(BlueprintCallable)
	virtual TArray<AHero*> GetHeroesInRow(ESquadRow Row) const override;

	UFUNCTION(BlueprintCallable)
	virtual AHero* GetLeader() const override;

	UFUNCTION(BlueprintCallable)
	virtual UObject* GetPlayerOwner() const override;

	UFUNCTION(BlueprintCallable)
	void AddHero(ADropZone* NewDropZone);

	UFUNCTION(BlueprintCallable)
	virtual void AddSquadEffect(FGameplayEffectSpecHandle EffectSpec) override;
	
	UFUNCTION(BlueprintCallable)
	virtual TArray<FGameplayEffectSpecHandle> GetSquadEffects() const override { return SquadEffects; }

	AHero* GetHero(ESquadRow Row, ESquadColumn Column) const;

private:
	UPROPERTY(EditAnywhere)
	TArray<ADropZone*> DropZones;
	TArray<FGameplayEffectSpecHandle> SquadEffects;
};
