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
	UFUNCTION(BlueprintCallable)
	static void Reset();
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject"))
	static void InitializePlayers(class APlayerPawn* FirstPlayerPawn, class APlayerPawn* SecondPlayerPawn);

	UFUNCTION(BlueprintCallable)
	static void ChangePlayerTurn();

	UFUNCTION(BlueprintCallable)
	static void ChangeActivePlayer();

	UFUNCTION(BlueprintCallable)
	static void ChangeLineTurn();

	UFUNCTION(BlueprintCallable)
	static class APlayerPawn* GetActivePlayer();

	UFUNCTION(BlueprintCallable)
	static class APlayerPawn* GetNotActivePlayer();

	UFUNCTION(BlueprintCallable)
	static class APlayerPawn* GetPlayerPawn(const int PlayerIndex);

	static EBattleState GetPlayerTurn();

	UFUNCTION(BlueprintCallable)
	static int GetPlayerTurnInt();

	static ESquadRow GetLineTurn();

	UFUNCTION(BlueprintCallable)
	static int GetLineTurnInt();

private:
	static void AddPlayer(APlayerPawn* Player);

private:
	static inline TArray<class APlayerPawn*> Players = {};

	static inline EBattleState PlayerTurn = EBattleState::FirstPlayerTurn;

	static inline ESquadRow LineTurn = ESquadRow::Vanguard;

	static inline bool IsFirstPlayerActive = true;
};
