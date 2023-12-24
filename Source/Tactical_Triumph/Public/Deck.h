#pragma once

#include "CoreMinimal.h"
#include "Engine/ObjectLibrary.h"
#include "Deck.generated.h"

class ACardLibrary;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TACTICAL_TRIUMPH_API UDeck : public UActorComponent
{
	GENERATED_BODY()

public:
	UDeck();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	ACardLibrary* CardLibrary;

	UPROPERTY(EditAnywhere)
	TArray<class UHeroData*> Cards;

	UObjectLibrary* DataAssetLibrary = nullptr;

public:
	UFUNCTION(BlueprintCallable)
	int GetCount() const;

	UFUNCTION(BlueprintCallable)
	UHeroData* GetNext();
};
