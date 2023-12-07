// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DropZone.h"
#include "ISquad.h"
#include "AbilitySystem/Hero.h"
#include "AbilitySystem/SquadLines.h"
#include "Components/ActorComponent.h"
#include "Squad.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICAL_TRIUMPH_API USquad : public UActorComponent, public ISquad
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	USquad();

	UFUNCTION(BlueprintCallable)
	virtual TArray<AHero*> GetHeroesInColumn(EColumn column) const override;

	UFUNCTION(BlueprintCallable)
	virtual void GetNeighbours(AHero* originHero, AHero* outForward, AHero* outBack) const override;

	UFUNCTION(BlueprintCallable)
	virtual ERow GetRow(AHero* hero) const override;

	UFUNCTION(BlueprintCallable)
	virtual TArray<AHero*> GetHeroesInRow(ERow row) const override;
	
	UFUNCTION(BlueprintCallable)
	virtual AHero* GetLeader() const override;
	
	UFUNCTION(BlueprintCallable)
	virtual UObject* GetPlayerOwner() const override;

	UFUNCTION(BlueprintCallable)
	void AddHero(ADropZone* NewDropZone);

	AHero* GetHero(ERow row, EColumn column) const;
	
protected:
	UPROPERTY(EditAnywhere)
	TArray<ADropZone*> DropZones;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
