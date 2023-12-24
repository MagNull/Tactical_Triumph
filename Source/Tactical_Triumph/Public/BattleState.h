// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SquadLines.h"
#include "UObject/NoExportTypes.h"
#include "BattleState.generated.h"

UENUM(BlueprintType)
enum class EBattleState
{
	FirstPlayerTurn = 0,
	SecondPlayerTurn = 1
};

UCLASS()
class UBattleState : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject"))
	static void InitializePlayers(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	static void ChangePlayerTurn();

	UFUNCTION(BlueprintCallable)
	static void ChangeLineTurn();

	UFUNCTION(BlueprintCallable)
	static APawn* GetPlayerPawn(const int PlayerIndex);

	UFUNCTION(BlueprintCallable)
	static EBattleState GetPlayerTurn();

	UFUNCTION(BlueprintCallable)
	static int GetPlayerTurnInt();

	UFUNCTION(BlueprintCallable)
	static ESquadRow GetLineTurn();

	UFUNCTION(BlueprintCallable)
	static int GetLineTurnInt();

private:
	static void AddPlayer(const UObject* WorldContextObject, const int PlayerIndex);

private:
	static inline TArray<class APawn*> Players = {};

	static inline EBattleState PlayerTurn = EBattleState::FirstPlayerTurn;

	static inline ESquadRow LineTurn = ESquadRow::Vanguard;
};
