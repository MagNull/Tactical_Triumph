#pragma once
#include "ISpellContext.h"

enum class ERow;

class AxisSpellContext : ISpellContext
{
public:
	AxisSpellContext(AHero* caster, ISquad* squad, ERow row);
	virtual AHero* GetCaster() const override { return Caster; };
	virtual ISquad* GetSquad() const override { return Squad; };
	virtual TArray<AHero*> GetTarget() const override;

private:
	AHero* Caster;
	ISquad* Squad;
	ERow Row;
};
