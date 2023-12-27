#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SquadLines.h"
#include "GameFramework/Actor.h"
#include "DropZone.generated.h"

class AHero;

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
	virtual void SetHero(AHero* NewHero);

	UFUNCTION(BlueprintCallable)
	bool IsCenter();

	UFUNCTION(BlueprintCallable)
	class APlayerPawn* GetPlayerOwner();

	void Clear();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESquadColumn Column;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESquadRow Row;

	FOnSetHero OnSetHero;

private:
	UPROPERTY(EditAnywhere)
	class APlayerPawn* PlayerOwnerPawn;

	AHero* Hero = nullptr;
};
