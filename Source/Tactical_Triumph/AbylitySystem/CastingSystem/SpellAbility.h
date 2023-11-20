#pragma once

#include "CoreMinimal.h"
#include "IAbility.h"
#include "SpellAbility.generated.h"

class ISpellTargeting;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TACTICAL_TRIUMPH_API USpellAbility : public UObject, public IAbility
{
	GENERATED_BODY()
public:
	virtual void Activate() override;
	virtual void Deactivate() override;
	void InitiateCasting();
private:
	UPROPERTY(EditAnywhere)
	TScriptInterface<ISpellTargeting> Targeting;
};
