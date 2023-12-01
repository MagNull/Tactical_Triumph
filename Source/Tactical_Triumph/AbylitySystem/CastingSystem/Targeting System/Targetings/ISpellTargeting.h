#pragma once
#include <ISpellTargeting.generated.h>

UINTERFACE(MinimalAPI, Blueprintable)
class USpellTargeting : public UInterface
{
	GENERATED_BODY()
};

class ISpellTargeting
{
	GENERATED_BODY()
public:
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual bool IsSuccessful();
};
