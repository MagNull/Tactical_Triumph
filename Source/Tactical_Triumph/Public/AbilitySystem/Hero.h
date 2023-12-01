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

protected:
	virtual void BeginPlay() override;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	void AddStartupAbilities();

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

protected:
	void HandleDamage(float DamageAmount, const FGameplayTagContainer DamageTags,
	                  UAbilitySystemComponent* DamageInstigator, UAbilitySystemComponent* Target);

	void HandleHealthChanged(float deltaValue, const FGameplayTagContainer& eventTags);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

private:
	bool bAbilitiesIsInitialized;


	UPROPERTY(EditAnywhere, Category = "Attributes")
	TObjectPtr<UHeroAttributeSet> Attributes;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TMap<FGameplayTag, TSubclassOf<UHeroGameplayAbility>> Abilities;
};
