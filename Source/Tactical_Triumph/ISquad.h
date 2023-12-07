#pragma once

class AHero;
enum class ERow;
enum class EColumn;

class ISquad
{
public:
	virtual ~ISquad() = default;
	virtual void GetNeighbours(AHero* originHero, AHero* forward, AHero* back) const = 0;
	virtual TArray<AHero*> GetHeroesInColumn(EColumn column) const  = 0;
	virtual ERow GetRow(AHero* hero) const = 0;
	virtual TArray<AHero*> GetHeroesInRow(ERow row) const = 0;
	virtual AHero* GetLeader() const = 0;
	virtual UObject* GetPlayerOwner() const = 0;
};
