#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hero.generated.h"

class USpellAbility;
enum class ERow;
class URowBenefit;

UCLASS()
class TACTICAL_TRIUMPH_API AHero : public AActor
{
	GENERATED_BODY()
	
public:	
	AHero();

protected:
	virtual void BeginPlay() override;

public:	
	const URowBenefit& GetActiveBenefit() const;
	const bool TryGetSpell(USpellAbility* spell) const;
private:
	UPROPERTY(EditAnywhere, Category = "Benefits")
	URowBenefit* VanguardBenefit;
	UPROPERTY(EditAnywhere, Category = "Benefits")
	URowBenefit* FlankBenefit;
	UPROPERTY(EditAnywhere, Category = "Benefits")
	URowBenefit* BackBenefit;

	TMap<ERow, URowBenefit*> RowBenefitsMap;
};
