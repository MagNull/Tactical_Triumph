// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IAbility.h"
#include "RowBenefit.h"
#include "PassiveAbility.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TACTICAL_TRIUMPH_API UPassiveAbility : public UObject, public IAbility
{
	GENERATED_BODY()
public:
	UPassiveAbility();
public:
	virtual void Activate() override;
	virtual void Deactivate() override;
private:
	int abob = 1;
};
