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

protected:
	virtual void BeginPlay() override;
	
public:	
	virtual void Tick(float DeltaTime) override;

	TArray<UHeroData*> LoadCards();

	UPROPERTY(EditAnywhere)
	FString FolderPathToAssets;
};
