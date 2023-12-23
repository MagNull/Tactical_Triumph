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

protected:
	AHero* Hero;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESquadColumn Column;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESquadRow Row;

	UPROPERTY(EditAnywhere)
	class APlayerPawn* PlayerOwnerPawn;

	UFUNCTION(BlueprintCallable)
	bool GetIsOccupied() const;

	UFUNCTION(BlueprintCallable)
	AHero* GetHero() const;

	FOnSetHero OnSetHero;

	UFUNCTION(BlueprintCallable)
	virtual void SetHero(AHero* NewHero);

	UFUNCTION(BlueprintCallable)
	bool IsCenter();
};
