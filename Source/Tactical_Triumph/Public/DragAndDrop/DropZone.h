#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/SquadLines.h"
#include "GameFramework/Actor.h"
#include "AbilitySystem/Hero.h"
#include "DropZone.generated.h"

class UGameplayEffect;

UCLASS()
class TACTICAL_TRIUMPH_API ADropZone : public AActor
{
	GENERATED_BODY()

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnSetHero, AHero*);

public:
	ADropZone();

	UFUNCTION(BlueprintCallable)
	int GetRowInt() const;

	UFUNCTION(BlueprintCallable)
	int GetColumnInt() const;
	
	UFUNCTION(BlueprintCallable)
	bool IsOccupied() const;

	UFUNCTION(BlueprintCallable)
	AHero* GetHero() const;

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetGrantedTag() const {return GrantedTag;}

	UFUNCTION(BlueprintCallable)
	virtual void SetHero(AHero* NewHero);

	UFUNCTION(BlueprintCallable)
	bool IsCenter();

	UFUNCTION(BlueprintCallable)
	void AddZoneEffect(const FGameplayEffectSpecHandle EffectHandle, UGameplayAbility* SourceAbility);

	void RemoveZoneEffect(TSubclassOf<UGameplayAbility> Ability);
	
	void Clear();
	
protected:
	UFUNCTION(BlueprintCallable)
	void ApplyGrantedTag(AHero* Hero);

	UFUNCTION(BlueprintCallable)
	void RemoveGrantedTag(AHero* Hero);
private:
	void RemoveZoneEffectsFromHero(AHero* Hero);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESquadColumn Column;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESquadRow Row;

	FOnSetHero OnSetHero;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* HeroSpawnPoint;
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APlayerPawn* PlayerOwnerPawn;

private:
	UPROPERTY(EditAnywhere, Category = "Position Tag")
	FGameplayTag GrantedTag;

	TArray<TTuple<FGameplayEffectSpecHandle, UClass*>> ZoneEffectPairs;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> InfiniteEffect;

	TObjectPtr<AHero> CurrentHero;
};
