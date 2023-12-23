#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "HeroAbilitySystemComponent.h"

#include "Hero.generated.h"

class UHeroAttributeSet;
class UGameplayEffect;

UCLASS()
class TACTICAL_TRIUMPH_API AHero : public AActor, public IAbilitySystemInterface
{
	friend UHeroAttributeSet;
	GENERATED_BODY()

public:
	AHero();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return Cast<UAbilitySystemComponent>(AbilitySystemComponent);
	}

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetAttack() const;

	UFUNCTION(BlueprintCallable)
	float GetDamageReduction() const;

	UFUNCTION(BlueprintCallable)
	float GetPresentDamage() const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDamageChanged(float DamageAmount, const FGameplayTagContainer DamageTags,
				   UAbilitySystemComponent* DamageInstigator, UAbilitySystemComponent* Target);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float deltaValue, const FGameplayTagContainer& eventTags);

	UFUNCTION(BlueprintImplementableEvent)
	void OnAttackChanged(float deltaValue, const FGameplayTagContainer& eventTags);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Mesh;

protected:
	void HandleDamageChanged(float DamageAmount, const FGameplayTagContainer DamageTags,
					  UAbilitySystemComponent* DamageInstigator, UAbilitySystemComponent* Target);

	void HandleHealthChanged(float deltaValue, const FGameplayTagContainer& eventTags);
	
	void HandleAttackChanged(float deltaValue, const FGameplayTagContainer& eventTags);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UHeroAbilitySystemComponent* AbilitySystemComponent;

private:
	UPROPERTY(EditAnywhere, Category = "Attributes")
	TObjectPtr<UHeroAttributeSet> Attributes;
};
