#pragma once

#include "CoreMinimal.h"
#include "DragAndDrop/DropZone.h"
#include "Templates/Tuple.h"
#include "ISquad.h"
#include "AbilitySystem/Hero.h"
#include "AbilitySystem/SquadLines.h"
#include "Components/ActorComponent.h"
#include "Squad.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TACTICAL_TRIUMPH_API USquad : public UActorComponent, public ISquad
{
	GENERATED_BODY()

public:
	USquad();

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable)
	virtual TArray<AHero*> GetHeroesInColumn(ESquadColumn Column) const override;

	UFUNCTION(BlueprintCallable)
	virtual TArray<AHero*> GetHeroesInRow(ESquadRow Row) const override;

	UFUNCTION(BlueprintCallable)
	virtual void GetNeighbours(AHero* OriginHero, AHero*& OutForward, AHero*& OutBack) const override;

	UFUNCTION(BlueprintCallable)
	AHero* GetForwardNeighbour(AHero* OriginHero);

	UFUNCTION(BlueprintCallable)
	AHero* GetBackNeighbour(AHero* OriginHero);

	UFUNCTION(BlueprintCallable)
	virtual ESquadRow GetRow(AHero* Hero) const override;

	UFUNCTION(BlueprintCallable)
	virtual ESquadColumn GetColumn(AHero* Hero) const override;

	UFUNCTION(BlueprintCallable)
	virtual AHero* GetLeader() override;

	AHero* GetHero(ESquadRow Row, ESquadColumn Column) const;

	UFUNCTION(BlueprintCallable)
	virtual UObject* GetPlayerOwner() const override;

	ADropZone* GetDropZone(ESquadRow row, ESquadColumn column) const;

	UFUNCTION(BlueprintCallable)
	ADropZone* GetCenterDropZone();
	UFUNCTION(BlueprintCallable)
	virtual void AddSquadEffect(TSubclassOf<UGameplayEffect> Effect) override;

	UFUNCTION(BlueprintCallable)
	virtual TArray<TSubclassOf<UGameplayEffect>> GetSquadEffects() const override { return SquadEffects; }

	UFUNCTION(BlueprintCallable)
	virtual void AddSquadAbility(TSubclassOf<UHeroGameplayAbility> Ability, bool activate) override;

	void OnSetHero(AHero* NewHero);

protected:
	UFUNCTION(BlueprintCallable)
	virtual TArray<TSubclassOf<UHeroGameplayAbility>> GetSquadAbilities() const override { return SquadAbilities; }

private:
	UPROPERTY(EditAnywhere)
	TArray<ADropZone*> DropZones;
	TArray<TSubclassOf<UGameplayEffect>> SquadEffects;
	TArray<TSubclassOf<UHeroGameplayAbility>> SquadAbilities;

	UPROPERTY(EditAnywhere)
	AHero* Leader;

	FDelegateHandle OnSetHeroHandle;
};
