#include "HeroSpellContext.h"

HeroSpellContext::HeroSpellContext(AHero* caster, ISquad* squad) : Caster(caster), Squad(squad)
{
}

TArray<AHero*> HeroSpellContext::GetTarget() const
{
	return TArray{Target};
}


