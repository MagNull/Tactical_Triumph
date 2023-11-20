#include "Hero.h"

#include "Tactical_Triumph/AbylitySystem/CastingSystem/RowBenefit.h"

// Sets default values
AHero::AHero()
{
	PrimaryActorTick.bCanEverTick = true;
	VanguardBenefit = CreateDefaultSubobject<URowBenefit>(TEXT("Vanguard Benefits"));
	FlankBenefit = CreateDefaultSubobject<URowBenefit>(TEXT("Flank Benefits"));
	BackBenefit = CreateDefaultSubobject<URowBenefit>(TEXT("Back Benefits"));
	
	RowBenefitsMap.Add(ERow::Vanguard, VanguardBenefit);
	RowBenefitsMap.Add(ERow::Flank, FlankBenefit);
	RowBenefitsMap.Add(ERow::Back, BackBenefit);
}

void AHero::BeginPlay()
{
	Super::BeginPlay();
}

const URowBenefit& AHero::GetActiveBenefit() const
{
	for (const auto RowAbility : RowBenefitsMap)
	{
		if(RowAbility.Value->IsActive())
			return *RowAbility.Value;
	}

	throw std::exception("There is no active benefit");
}

