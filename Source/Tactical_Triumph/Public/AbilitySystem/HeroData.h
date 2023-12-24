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

	UFUNCTION(BlueprintCallable, Category = "View")
	USkeletalMesh* GetMesh() const { return Mesh; }

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	TMap<FGameplayTag, TSubclassOf<UHeroGameplayAbility>> GetAbilities() const { return Abilities; };

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "View")
	FString Name;
	UPROPERTY
	(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "View")
	USkeletalMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TMap<FGameplayTag, TSubclassOf<UHeroGameplayAbility>> Abilities;
};
