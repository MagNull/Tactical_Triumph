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
	
public:	
	ADropZone();

protected:
	bool IsOccupied;
	AHero* Hero;
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESquadColumn Column;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESquadRow Row;
	
	UFUNCTION(BlueprintCallable)
	bool GetIsOccupied() const;

	UFUNCTION(BlueprintCallable)
	AHero* GetHero() const;
	
	UFUNCTION(BlueprintCallable)
	void SetHero(AHero* NewHero);
};
