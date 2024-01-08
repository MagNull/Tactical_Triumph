// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/PlayerAttributeSet.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class USquadComponent;
class UDeckComponent;
class UPlayerAttributeSet;
class UDA_Card;
class UAbilitySystemComponent;

UCLASS()
class TACTICAL_TRIUMPH_API APlayerPawn : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()
	friend UPlayerAttributeSet;

public:
	APlayerPawn();
	
	virtual void BeginPlay() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	
	UFUNCTION(BlueprintCallable)
	int GetActionPoints() const { return Attributes->GetActionPoints(); }

	UFUNCTION(BlueprintCallable)
	int GetActionPointsRestoration() const { return Attributes->GetActionPointsRestoration(); }

	UFUNCTION(BlueprintImplementableEvent)	
	void OnActionPointsChanged(int NewValue);

private:
	void HandleActionPointsChanged();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(EditAnywhere, Category = "Attributes")
	TObjectPtr<UPlayerAttributeSet> Attributes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDeckComponent* Deck;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USquadComponent* SquadComponent;
};
