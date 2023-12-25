#pragma once
#include "CoreMinimal.h"
#include "DragAndDrop/DropZone.h"
#include "Templates/Tuple.h"
#include "AbilitySystem/Hero.h"
#include "AbilitySystem/SquadLines.h"
#include "Components/ActorComponent.h"
#include "Squad.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TACTICAL_TRIUMPH_API USquad : public UActorComponent
{
	GENERATED_BODY()

public:
	USquad();

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable)
	virtual TArray<AHero*> GetHeroesInColumn(ESquadColumn Column) const;

	UFUNCTION(BlueprintCallable)
	virtual TArray<AHero*> GetHeroesInRow(ESquadRow Row) const;

	UFUNCTION(BlueprintCallable)
	virtual TArray<AHero*> GetHeroes() const;
	virtual void GetNeighbours(AHero* OriginHero, AHero*& OutForward, AHero*& OutBack) const;

	UFUNCTION(BlueprintCallable)
	AHero* GetForwardNeighbour(AHero* OriginHero);

	UFUNCTION(BlueprintCallable)
	AHero* GetBackNeighbour(AHero* OriginHero);

	UFUNCTION(BlueprintCallable)
	virtual ESquadRow GetRow(AHero* Hero) const;

	UFUNCTION(BlueprintCallable)
	virtual ESquadColumn GetColumn(AHero* Hero) const;

	UFUNCTION(BlueprintCallable)
	virtual AHero* GetLeader();

	AHero* GetHero(ESquadRow Row, ESquadColumn Column) const;

	UFUNCTION(BlueprintCallable)
	virtual UObject* GetPlayerOwner() const;

	ADropZone* GetDropZone(ESquadRow row, ESquadColumn column) const;
	UFUNCTION(BlueprintCallable)
	ADropZone* GetCenterDropZone();
	
	UFUNCTION(BlueprintCallable)
	virtual void AddSquadEffect(FGameplayEffectSpecHandle Effect);

	UFUNCTION(BlueprintCallable)
	virtual TArray<FGameplayEffectSpecHandle> GetSquadEffects() const { return SquadEffects; }

	UFUNCTION(BlueprintCallable)
	virtual void AddSquadAbility(TSubclassOf<UHeroGameplayAbility> Ability, bool activate);

	void OnSetHero(AHero* NewHero);

protected:
	UFUNCTION(BlueprintCallable)
	virtual TArray<TSubclassOf<UHeroGameplayAbility>> GetSquadAbilities() const { return SquadAbilities; }

private:
	UPROPERTY(EditAnywhere)
	TArray<ADropZone*> DropZones;
	TArray<FGameplayEffectSpecHandle> SquadEffects;
	TArray<TSubclassOf<UHeroGameplayAbility>> SquadAbilities;

	UPROPERTY(EditAnywhere)
	AHero* Leader;

	FDelegateHandle OnSetHeroHandle;
};
