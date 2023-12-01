#include "RowBenefit.h"

#include "Tactical_Triumph/ISquad.h"
#include "Tactical_Triumph/Hero/Hero.h"

URowBenefit::URowBenefit()
{
	HeroOwner = Cast<AHero>(GetOwner());
}

void URowBenefit::OnPositionChanged(ISquad* squad)
{
	
}

