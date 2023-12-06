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
	Vanguard = 0 UMETA(DisplayName = "Авангард"),
	Flank = 1 UMETA(DisplayName = "Фланк"),
	Back = 2 UMETA(DisplayName = "Тыл")
};

UENUM(BlueprintType)
enum class EColumn
{
	Left = 0 UMETA(DisplayName = "Левый"),
	Mid = 1 UMETA(DisplayName = "Центр"),
	Right = 2 UMETA(DisplayName = "Правый")
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
