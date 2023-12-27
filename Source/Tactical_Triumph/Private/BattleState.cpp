#include "BattleState.h"
#include "Pawn/PlayerPawn.h"

void UBattleState::Reset()
{
	Players = {};
	ResetWithoutPlayers();
}

void UBattleState::ResetWithoutPlayers()
{
	StartPlayerIndex = 1;
	LineTurn = ESquadRow::Vanguard;
	IsFirstPlayerActive = true;
	TurnCount = 1;
}

void UBattleState::InitializePlayers(APlayerPawn* FirstPlayerPawn, APlayerPawn* SecondPlayerPawn)
{
	while (!Players.IsEmpty())
	{
		Players.RemoveAt(0);
	}
	AddPlayer(FirstPlayerPawn);
	AddPlayer(SecondPlayerPawn);
}

void UBattleState::ChangeStartPlayerIndex()
{
	StartPlayerIndex += 1;
	StartPlayerIndex %= 2;
}

void UBattleState::ChangeActivePlayer()
{
	IsFirstPlayerActive = !IsFirstPlayerActive;
	UE_LOG(LogTemp, Display, TEXT("Active player: %d"), IsFirstPlayerActive);
}

void UBattleState::ChangeLineTurn()
{
	LineTurn = static_cast<ESquadRow>((static_cast<int>(LineTurn) + 1) % sizeof(ESquadRow));
}

APlayerPawn* UBattleState::GetActivePlayer()
{
	UE_LOG(LogTemp, Display, TEXT("Players Num: %d"), Players.Num());
	if (Players.IsEmpty() || Players.Num() < 2)
		return nullptr;
	return IsFirstPlayerActive ? Players[0] : Players[1];
}

APlayerPawn* UBattleState::GetNotActivePlayer()
{
	if (Players.IsEmpty() || Players.Num() < 2)
		return nullptr;
	return IsFirstPlayerActive ? Players[1] : Players[0];
}

APlayerPawn* UBattleState::GetAttackPlayer()
{
	return Players[StartPlayerIndex];
}

APlayerPawn* UBattleState::GetDefensePlayer()
{
	return Players[(StartPlayerIndex + 1) % 2];
}

int UBattleState::GetStartPlayerIndex()
{
	return StartPlayerIndex;
}

int UBattleState::GetActivePlayerIndex()
{
	return IsFirstPlayerActive;
}

APlayerPawn* UBattleState::GetPlayerPawn(const int PlayerIndex)
{
	return Players.Num() > PlayerIndex ? Players[PlayerIndex] : nullptr;
}

ESquadRow UBattleState::GetLineTurn()
{
	return LineTurn;
}

int UBattleState::GetLineTurnInt()
{
	return static_cast<int>(LineTurn);
}

void UBattleState::AddTurnCount()
{
	TurnCount += 1;
}

int UBattleState::GetTurnCount()
{
	return TurnCount;
}

void UBattleState::AddPlayer(APlayerPawn* Player)
{
	if (Player == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Player Pawn is not valid or null"));
	}
	else
	{
		Players.Add(Player);
	}
}
