#include "AxisSpellContext.h"

#include "Tactical_Triumph/ISquad.h"

AxisSpellContext::AxisSpellContext(AHero* caster, ISquad* squad, ERow row) : Caster(caster), Squad(squad), Row(row)
{
}

TArray<AHero*> AxisSpellContext::GetTarget() const
{
	TArray<AHero*> result = Squad->GetHeroesInRow(Row);
	return result;
}
