// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"

#include "GASHeroTest.generated.h"

UCLASS()
class TACTICAL_TRIUMPH_API AGASHeroTest : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGASHeroTest();

protected:
	virtual void BeginPlay() override;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	UAbilitySystemComponent* AbilitySystemComponent;
};
