#pragma once

class AHero;
enum class ESquadRow;
enum class ESquadColumn;

class ISquad
{
public:
	virtual ~ISquad() = default;
	virtual void GetNeighbours(AHero* originHero, AHero* forward, AHero* back) const = 0;
	virtual TArray<AHero*> GetHeroesInColumn(ESquadColumn column) const  = 0;
	virtual ESquadRow GetRow(AHero* hero) const = 0;
	virtual TArray<AHero*> GetHeroesInRow(ESquadRow row) const = 0;
	virtual AHero* GetLeader() = 0;
	virtual UObject* GetPlayerOwner() const = 0;
};
