#pragma once

class ISquad;
class AHero;

class ISpellContext
{
public:
	virtual AHero* GetCaster() const = 0;
	virtual TArray<AHero*> GetTarget() const = 0;
	virtual ISquad* GetSquad() const = 0;
};
