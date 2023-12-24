#include "BattleState.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/PlayerPawn.h"

void UBattleState::ChangePlayerTurn()
{
	PlayerTurn = PlayerTurn == EBattleState::FirstPlayerTurn
		             ? EBattleState::SecondPlayerTurn
		             : EBattleState::FirstPlayerTurn;
}

void UBattleState::ChangeLineTurn()
{
	LineTurn = static_cast<ESquadRow>((static_cast<int>(LineTurn) + 1) % sizeof(ESquadRow));
}

APawn* UBattleState::GetPlayerPawn(const int PlayerIndex)
{
	return Players.Num() > PlayerIndex ? Players[PlayerIndex] : nullptr;
}

void UBattleState::InitializePlayers(UObject* WorldContextObject)
{
	while (!Players.IsEmpty())
	{
		Players.RemoveAt(0);
	}
	AddPlayer(WorldContextObject, 0);
	AddPlayer(WorldContextObject, 1);
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

void UBattleState::AddPlayer(const UObject* WorldContextObject, const int PlayerIndex)
{
	if (APlayerPawn* PlayerPawn = static_cast<APlayerPawn*>(UGameplayStatics::GetPlayerPawn(
			WorldContextObject->GetWorld(), PlayerIndex));
		PlayerPawn == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Player Pawn with index %d is null"), PlayerIndex);
	}
	else
	{
		Players.Add(PlayerPawn);
	}
}
