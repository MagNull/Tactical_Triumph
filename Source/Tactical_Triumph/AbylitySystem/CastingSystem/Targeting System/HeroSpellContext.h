#pragma once
#include "ISpellContext.h"

class HeroSpellContext : ISpellContext
{
public:
	HeroSpellContext(AHero* caster, ISquad* squad);
	virtual AHero* GetCaster() const override { return Caster; };
	virtual ISquad* GetSquad() const override { return Squad; };
	virtual TArray<AHero*> GetTarget() const override;
private:
	AHero* Caster;
	ISquad* Squad;
	AHero* Target;
};
