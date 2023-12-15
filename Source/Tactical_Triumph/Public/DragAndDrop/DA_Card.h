// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_Card.generated.h"

/**
 * 
 */
UCLASS()
class TACTICAL_TRIUMPH_API UDA_Card : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	FString GetCharacterName() { return CharacterName; }
	
	UFUNCTION(BlueprintCallable)
	UTexture2D* GetImage() { return Image; }
	
	UFUNCTION(BlueprintCallable)
	int GetAttack() { return Attack; }
	
	UFUNCTION(BlueprintCallable)
	int GetHP() { return HP; }

	UFUNCTION(BlueprintCallable)
	FText GetAvanguardDescription() { return AvanguardDescription; }

	UFUNCTION(BlueprintCallable)
	FText GetMiddleDescription() { return MiddleDescription; }
	
	UFUNCTION(BlueprintCallable)
	FText GetBackDescription() { return BackDescription; }

	UFUNCTION(BlueprintCallable)
	FText GetOrderDescription() { return OrderDescription; }

	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetMesh() { return Mesh; }

	UFUNCTION(BlueprintCallable)
	AHero* GetHero() { return Hero; }
	
	UPROPERTY(EditAnywhere, Category = "CardData")
	FString CharacterName;

	UPROPERTY(EditAnywhere, Category = "CardData")
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, Category = "CardData")
	int Attack;

	UPROPERTY(EditAnywhere, Category = "CardData")
	int HP;

	UPROPERTY(EditAnywhere, Category = "CardData")
	FText AvanguardDescription;

	UPROPERTY(EditAnywhere, Category = "CardData")
	FText MiddleDescription;

	UPROPERTY(EditAnywhere, Category = "CardData")
	FText BackDescription;

	UPROPERTY(EditAnywhere, Category = "CardData")
	FText OrderDescription;

	UPROPERTY(EditAnywhere, Category = "CardData")
	UStaticMesh* Mesh;
	
	UPROPERTY(EditAnywhere, Category = "CardData")
	AHero* Hero;
};
