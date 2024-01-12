// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "PlayerAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class TACTICAL_TRIUMPH_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	UFUNCTION()
	virtual void OnRep_ActionPoints(const FGameplayAttributeData oldData);
	UFUNCTION()
	virtual void OnRep_ActionPointsRestoration(const FGameplayAttributeData oldData);

public:
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_ActionPoints)
	FGameplayAttributeData ActionPoints;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, ActionPoints);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxActionPoints;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaxActionPoints);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_ActionPoints)
	FGameplayAttributeData ActionPointsRestoration;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, ActionPointsRestoration);
};
