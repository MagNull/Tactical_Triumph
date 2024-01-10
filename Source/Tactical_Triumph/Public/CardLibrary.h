// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardLibrary.generated.h"

class UHeroData;

UCLASS()
class TACTICAL_TRIUMPH_API ACardLibrary : public AActor
{
	GENERATED_BODY()
	
public:	
	ACardLibrary();

	UFUNCTION(BlueprintCallable)
	TArray<UHeroData*> LoadCards();

private:
	UPROPERTY(EditAnywhere)
	FString FolderPathToAssets;

	UPROPERTY(EditAnywhere)
	TArray<UHeroData*> HeroData;
};
