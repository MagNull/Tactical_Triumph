#pragma once

struct FGameplayEffectSpecHandle;
class AHero;
enum class ESquadRow;
enum class ESquadColumn;

class ISquad
{
public:
	virtual ~ISquad() = default;
	virtual void GetNeighbours(AHero* OriginHero, AHero* OutForward, AHero* OutBack) const = 0;
	virtual TArray<AHero*> GetHeroesInColumn(ESquadColumn Column) const = 0;
	virtual ESquadRow GetRow(AHero* Hero) const = 0;
	virtual TArray<AHero*> GetHeroesInRow(ESquadRow Row) const = 0;
	virtual AHero* GetLeader() const = 0;
	virtual UObject* GetPlayerOwner() const = 0;
	virtual void AddSquadEffect(FGameplayEffectSpecHandle EffectSpec) = 0;
	virtual TArray<FGameplayEffectSpecHandle> GetSquadEffects() const = 0;
};
