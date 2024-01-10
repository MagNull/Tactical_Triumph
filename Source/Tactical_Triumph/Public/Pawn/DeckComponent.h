// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DeckComponent.generated.h"


class ACardLibrary;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICAL_TRIUMPH_API UDeckComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDeckComponent();
	
	UFUNCTION(BlueprintCallable)
	int GetCount() const;

	UFUNCTION(BlueprintCallable)
	class UHeroData* Pop();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TArray<UHeroData*> HeroData;
	// UPROPERTY(EditAnywhere)
	// ACardLibrary* CardLibrary;

	TArray<class UHeroData*> CardsInDeck;
	bool isInit = false;

};
