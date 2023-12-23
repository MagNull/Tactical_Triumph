#pragma once

class UGameplayEffect;
class UHeroGameplayAbility;
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
	virtual TArray<AHero*> GetHeroesInRow(ESquadRow Row) const = 0;
	virtual TArray<AHero*> GetHeroes() const = 0;

	virtual ESquadRow GetRow(AHero* Hero) const = 0;
	virtual ESquadColumn GetColumn(AHero* Hero) const = 0;

	virtual AHero* GetLeader() const = 0;

	virtual UObject* GetPlayerOwner() const = 0;


	virtual void AddSquadEffect(TSubclassOf<UGameplayEffect> EffectSpec) = 0;
	virtual TArray<TSubclassOf<UGameplayEffect>> GetSquadEffects() const = 0;
	
	virtual void AddSquadAbility(TSubclassOf<UHeroGameplayAbility> Ability, bool activate) = 0;
	virtual TArray<TSubclassOf<UHeroGameplayAbility>> GetSquadAbilities() const = 0;
};
