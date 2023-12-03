#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"

#include "Hero.generated.h"

class UHeroAttributeSet;
class UHeroGameplayAbility;
class UGameplayEffect;

UCLASS()
class TACTICAL_TRIUMPH_API AHero : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AHero();
	friend UHeroAttributeSet;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	UFUNCTION(BlueprintCallable)
	void GrantAbilityWithLineTag(TSubclassOf<UHeroGameplayAbility> ability, FGameplayTag TriggerTag);

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
	void OnDamaged(float DamageAmount, const FGameplayTagContainer DamageTags,
	               UAbilitySystemComponent* DamageInstigator, UAbilitySystemComponent* Target);


	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float deltaValue, const FGameplayTagContainer& eventTags);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Mesh;

protected:
	void HandleDamage(float DamageAmount, const FGameplayTagContainer DamageTags,
	                  UAbilitySystemComponent* DamageInstigator, UAbilitySystemComponent* Target);

	void HandleHealthChanged(float deltaValue, const FGameplayTagContainer& eventTags);


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystemComponent;

private:
	UPROPERTY(EditAnywhere, Category = "Attributes")
	TObjectPtr<UHeroAttributeSet> Attributes;
};
