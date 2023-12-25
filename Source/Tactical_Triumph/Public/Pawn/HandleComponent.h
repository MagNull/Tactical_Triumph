// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HandleComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TACTICAL_TRIUMPH_API UHandleComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHandleComponent();

	UFUNCTION(BlueprintCallable)
	void AddCard(class UHeroData* NewCard);

	UFUNCTION(BlueprintCallable)
	void RemoveCard(class UHeroData* CardToRemove);

	UFUNCTION(BlueprintCallable)
	TArray<class UHeroData*> GetCards();

private:
	UPROPERTY(EditAnywhere)
	TArray<class UHeroData*> Cards;
};
