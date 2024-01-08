// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SquadLines.h"
#include "UObject/NoExportTypes.h"
#include "BattleState.generated.h"

UCLASS()
class UBattleState : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void Reset();
	
	UFUNCTION(BlueprintCallable)
	static void ResetWithoutPlayers();
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject"))
	static void InitializePlayers(class APlayerPawn* FirstPlayerPawn, class APlayerPawn* SecondPlayerPawn);

	UFUNCTION(BlueprintCallable)
	static void ChangeStartPlayerIndex();

	UFUNCTION(BlueprintCallable)
	static void ChangeActivePlayer();

	UFUNCTION(BlueprintCallable)
	static void ChangeLineTurn();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static class APlayerPawn* GetActivePlayer();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static class APlayerPawn* GetNotActivePlayer();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static class APlayerPawn* GetAttackPlayer();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static class APlayerPawn* GetDefensePlayer();

	UFUNCTION(BlueprintCallable)
	static int GetStartPlayerIndex();

	UFUNCTION(BlueprintCallable)
	static int GetActivePlayerIndex();

	UFUNCTION(BlueprintCallable)
	static class APlayerPawn* GetPlayerPawn(const int PlayerIndex);

	static ESquadRow GetLineTurn();

	UFUNCTION(BlueprintCallable)
	static int GetLineTurnInt();

	UFUNCTION(BlueprintCallable)
	static void AddTurnCount();
	
	UFUNCTION(BlueprintCallable)
	static int GetTurnCount();

private:
	static void AddPlayer(APlayerPawn* Player);

private:
	static inline TArray<class APlayerPawn*> Players = {};
	
	static inline int StartPlayerIndex = 0;

	static inline ESquadRow LineTurn = ESquadRow::Vanguard;

	static inline bool IsFirstPlayerActive = true;

	static inline int TurnCount = 1;
};
