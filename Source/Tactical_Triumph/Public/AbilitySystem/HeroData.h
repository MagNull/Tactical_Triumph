#pragma once

#include "CoreMinimal.h"
#include "HeroGameplayAbility.h"
#include "Engine/DataAsset.h"
#include "HeroData.generated.h"


UCLASS(BlueprintType)
class TACTICAL_TRIUMPH_API UHeroData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "View")
	FString GetName() const { return Name; }

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetAttack() const { return Attack; }

	UFUNCTION(BlueprintCallable, Category = "Leder Attributes")
	float GetLeaderAttack() const { return LeaderAttack; }

	UFUNCTION(BlueprintCallable, Category = "Leder Attributes")
	float GetLeaderHealth() const { return LeaderHealth; }

	UFUNCTION(BlueprintCallable, Category = "Ability Descriptions")
	FText GetLeaderAbilityDescription() const { return LeaderAbilityDescription; }

	UFUNCTION(BlueprintCallable, Category = "Ability Descriptions")
	FText GetShortLeaderAbilityDescription() const { return LeaderAbilityShortDescription; }

	UFUNCTION(BlueprintCallable, Category = "Ability Descriptions")
	FText GetVanguardAbilityDescription() const { return VanguardAbilityDescription; }

	UFUNCTION(BlueprintCallable, Category = "Ability Descriptions")
	FText GetShortVanguardAbilityDescription() const { return VanguardAbilityShortDescription; }

	UFUNCTION(BlueprintCallable, Category = "Ability Descriptions")
	FText GetFlankAbilityDescription() const { return FlankAbilityDescription; }

	UFUNCTION(BlueprintCallable, Category = "Ability Descriptions")
	FText GetShortFlankAbilityDescription() const { return FlankAbilityShortDescription; }

	UFUNCTION(BlueprintCallable, Category = "Ability Descriptions")
	FText GetBackAbilityDescription() const { return BackAbilityDescription; }

	UFUNCTION(BlueprintCallable, Category = "Ability Descriptions")
	FText GetShortBackAbilityDescription() const { return BackAbilityShortDescription; }

	
	UFUNCTION(BlueprintCallable, Category = "View")
	USkeletalMesh* GetMesh() const { return Mesh; }

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	TMap<FGameplayTag, TSubclassOf<UHeroGameplayAbility>> GetAbilities() const { return Abilities; };

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "View")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leader Attributes")
	float LeaderHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leader Attributes")
	float LeaderAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "View")
	USkeletalMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TMap<FGameplayTag, TSubclassOf<UHeroGameplayAbility>> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Descriptions")
	FText LeaderAbilityDescription;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Descriptions")
	FText LeaderAbilityShortDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Descriptions")
	FText VanguardAbilityDescription;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Descriptions")
	FText VanguardAbilityShortDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Descriptions")
	FText FlankAbilityDescription;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Descriptions")
	FText FlankAbilityShortDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Descriptions")
	FText BackAbilityDescription;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Descriptions")
	FText BackAbilityShortDescription;
};
