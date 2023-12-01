#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IAbility.h"
#include "RowBenefit.generated.h"

class AHero;
class ISquad;

UENUM(BlueprintType)
enum class ERow
{
	Vanguard UMETA(DisplayName = "Авангард"),
	Flank UMETA(DisplayName = "Фланк"),
	Back UMETA(DisplayName = "Тыл")
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TACTICAL_TRIUMPH_API URowBenefit : public UActorComponent
{
	GENERATED_BODY()

public:
	URowBenefit();
	void OnPositionChanged(ISquad* squad);
	bool IsActive() const { return bIsActive; }

private:
	UPROPERTY(EditAnywhere)
	ERow ActivationRow;
	UPROPERTY(EditAnywhere)
	TScriptInterface<IAbility> Ability;

	AHero* HeroOwner;
	bool bIsActive;
};
