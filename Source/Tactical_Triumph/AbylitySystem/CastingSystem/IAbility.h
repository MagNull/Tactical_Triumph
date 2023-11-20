#pragma once

#include<IAbility.generated.h>

UINTERFACE(MinimalAPI, Blueprintable)
class UAbility : public UInterface
{
	GENERATED_BODY()
};

class IAbility
{
	GENERATED_BODY()
public:
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;
};
