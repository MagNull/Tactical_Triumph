#pragma once

#include "CoreMinimal.h"
#include "DragAndDrop/DropZone.h"
#include "Templates/Tuple.h"
#include "AbilitySystem/Hero.h"
#include "AbilitySystem/SquadLines.h"
#include "Components/ActorComponent.h"
#include "SquadComponent.generated.h"

USTRUCT(BlueprintType)
struct FSquadAbility
{
	GENERATED_BODY()

	TSubclassOf<UGameplayAbility> Ability;
	TSubclassOf<UGameplayAbility> SourceAbility;

	bool operator==(const FSquadAbility&) const;
};

USTRUCT(BlueprintType)
struct FSquadEffect
{
	GENERATED_BODY()

	FGameplayEffectSpecHandle EffectSpecHandle;
	TSubclassOf<UGameplayAbility> SourceAbility;

	bool operator==(const FSquadEffect&) const;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TACTICAL_TRIUMPH_API USquadComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USquadComponent();

	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable)
	void RemoveHero(AHero* Hero);

	UFUNCTION(BlueprintCallable)
	bool TryMoveHeroTo(AHero* Hero, ESquadRow row, ESquadColumn column);

	UFUNCTION(BlueprintCallable)
	TArray<AHero*> GetHeroesInColumn(ESquadColumn Column) const;

	UFUNCTION(BlueprintCallable)
	TArray<AHero*> GetHeroesInRow(ESquadRow Row) const;

	UFUNCTION(BlueprintCallable)
	TArray<ADropZone*> GetDropZonesInRow(ESquadRow Row) const;

	UFUNCTION(BlueprintCallable)
	TArray<ADropZone*> GetDropZonesInColumn(ESquadColumn Column) const;

	UFUNCTION(BlueprintCallable)
	TArray<AHero*> GetHeroes() const;
	void GetNeighbours(AHero* OriginHero, ADropZone*& OutForward, ADropZone*& OutBack) const;

	UFUNCTION(BlueprintCallable)
	ADropZone* GetForwardNeighbour(AHero* OriginHero);

	UFUNCTION(BlueprintCallable)
	ADropZone* GetBackNeighbour(AHero* OriginHero);

	UFUNCTION(BlueprintCallable)
	ESquadRow GetRow(AHero* Hero) const;

	UFUNCTION(BlueprintCallable)
	ESquadColumn GetColumn(AHero* Hero) const;

	UFUNCTION(BlueprintCallable)
	AHero* GetLeader();

	UFUNCTION(BlueprintCallable)
	UObject* GetPlayerOwner() const;

	UFUNCTION(BlueprintCallable)
	ADropZone* GetCenterDropZone();

	UFUNCTION(BlueprintCallable)
	TArray<AHero*> GetFirstHeroesInColumns() const;

	UFUNCTION(BlueprintCallable)
	TArray<AHero*> GetForwardHeroes(AHero* Hero) const;

	UFUNCTION(BlueprintCallable)
	ADropZone* GetDropZoneByHero(AHero* Hero) const;

	UFUNCTION(BlueprintCallable)
	void AddSquadAbility(FSquadAbility SquadAbility, bool activate);

	UFUNCTION(BlueprintCallable)
	void RemoveSquadAbility(TSubclassOf<UGameplayAbility> SourceAbility);

	UFUNCTION(BlueprintCallable)
	void AddSquadEffect(FSquadEffect SquadEffect);

	UFUNCTION(BlueprintCallable)
	void RemoveSquadEffect(TSubclassOf<UGameplayAbility> SourceAbility);

	UFUNCTION(BlueprintCallable)
	void RemoveDropZoneEffect(TSubclassOf<UGameplayAbility> SourceAbility);

	UFUNCTION(BlueprintCallable)
	TArray<ADropZone*> GetDropZoneInRow(int RowNumber);

protected:
	AHero* GetHero(ESquadRow Row, ESquadColumn Column) const;

	void OnSetHero(AHero* NewHero);

	ADropZone* GetDropZone(ESquadRow row, ESquadColumn column) const;

private:
	
	
	AHero* FirstHeroInArray(TArray<AHero*> Heroes) const;

private:
	UPROPERTY(EditAnywhere)
	TArray<ADropZone*> DropZones;
	TArray<FSquadEffect> SquadEffects;
	TArray<FSquadAbility> SquadAbilities;

	UPROPERTY(EditAnywhere)
	AHero* Leader;

	FDelegateHandle OnSetHeroHandle;
};
