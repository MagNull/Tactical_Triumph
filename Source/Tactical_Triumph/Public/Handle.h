#pragma once

#include "CoreMinimal.h"
#include "Engine/ObjectLibrary.h"
#include "Handle.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICAL_TRIUMPH_API UHandle : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHandle();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TArray<class UDA_Card*> Cards;

	UObjectLibrary* DataAssetLibrary = nullptr;

public:
	UFUNCTION(BlueprintCallable)
	void LoadCards();
	
	UFUNCTION(BlueprintCallable)
	int GetCount() const;

	UFUNCTION(BlueprintCallable)
	UDA_Card* GetNext();
};
