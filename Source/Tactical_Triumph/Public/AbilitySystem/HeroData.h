// Fill out your copyright notice in the Description page of Project Settings.

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
	UFUNCTION(BlueprintCallable)
	float GetHealth() const {return Health;}

	UFUNCTION(BlueprintCallable)
	float GetAttack() const {return Attack;}

	UFUNCTION(BlueprintCallable)
	USkeletalMesh* GetMesh() const {return Mesh;}

	UFUNCTION(BlueprintCallable)
	TMap<FGameplayTag, TSubclassOf<UHeroGameplayAbility>>  GetAbilities() const {return Abilities;};

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, TSubclassOf<UHeroGameplayAbility>> Abilities;
	
};
