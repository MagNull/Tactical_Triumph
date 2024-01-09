#include "BattleState.h"
#include "Pawn/PlayerPawn.h"

void UBattleState::Reset()
{
	Players = {};
	ResetWithoutPlayers();
}

void UBattleState::ResetWithoutPlayers()
{
	StartPlayerIndex = 0;
	LineTurn = ESquadRow::Vanguard;
	IsFirstPlayerActive = false;
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
	LineTurn = static_cast<ESquadRow>((static_cast<int>(LineTurn) + 1) % 3);
	UE_LOG(LogTemp, Display, TEXT("LineTurn: %d"), static_cast<int>(LineTurn));
}

APlayerPawn* UBattleState::GetActivePlayer()
{
	if (Players.IsEmpty() || Players.Num() < 2)
	{
		UE_LOG(LogTemp, Error, TEXT("There is not any players!"));
		return nullptr;
	}
	return IsFirstPlayerActive ? Players[1] : Players[0];
}

APlayerPawn* UBattleState::GetOtherPlayer(APlayerPawn* Player)
{
	for (auto PlayerPawn : Players)
	{
		if (PlayerPawn != Player)
			return PlayerPawn;
	}
	return nullptr;
}

APlayerPawn* UBattleState::GetNotActivePlayer()
{
	if (Players.IsEmpty() || Players.Num() < 2)
		return nullptr;
	return IsFirstPlayerActive ? Players[0] : Players[1];
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
	UE_LOG(LogTemp, Display, TEXT("Line turn - %p"), GetLineTurnInt);
	return LineTurn;
}

int UBattleState::GetLineTurnInt()
{
	return static_cast<int>(LineTurn);
}

void UBattleState::AddRoundCount()
{
	TurnCount += 1;
}

int UBattleState::GetRoundCount()
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
