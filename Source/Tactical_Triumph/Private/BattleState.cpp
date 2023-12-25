#include "BattleState.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/PlayerPawn.h"

void UBattleState::Reset()
{
	Players = {};
	PlayerTurn = EBattleState::FirstPlayerTurn;
	LineTurn = ESquadRow::Vanguard;
	IsFirstPlayerActive = true;
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

void UBattleState::ChangePlayerTurn()
{
	PlayerTurn = PlayerTurn == EBattleState::FirstPlayerTurn
		             ? EBattleState::SecondPlayerTurn
		             : EBattleState::FirstPlayerTurn;
}

void UBattleState::ChangeActivePlayer()
{
	IsFirstPlayerActive = !IsFirstPlayerActive;
}

void UBattleState::ChangeLineTurn()
{
	LineTurn = static_cast<ESquadRow>((static_cast<int>(LineTurn) + 1) % sizeof(ESquadRow));
}

APlayerPawn* UBattleState::GetActivePlayer()
{
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

APlayerPawn* UBattleState::GetPlayerPawn(const int PlayerIndex)
{
	return Players.Num() > PlayerIndex ? Players[PlayerIndex] : nullptr;
}

EBattleState UBattleState::GetPlayerTurn()
{
	return PlayerTurn;
}

int UBattleState::GetPlayerTurnInt()
{
	return static_cast<int>(PlayerTurn);
}

ESquadRow UBattleState::GetLineTurn()
{
	return LineTurn;
}

int UBattleState::GetLineTurnInt()
{
	return static_cast<int>(LineTurn);
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
