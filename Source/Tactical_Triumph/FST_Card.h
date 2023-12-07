// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FST_Card.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct TACTICAL_TRIUMPH_API FST_Card
{
	GENERATED_BODY()
 	
	FST_Card();
	~FST_Card();

	UPROPERTY(BlueprintReadWrite)
	FString character_name;

	UPROPERTY(BlueprintReadWrite)
	UTexture2D* image;

	UPROPERTY(BlueprintReadWrite)
	int attack;

	UPROPERTY(BlueprintReadWrite)
	int hp;
	
	UPROPERTY(BlueprintReadWrite)
	FText avangard_description;

	UPROPERTY(BlueprintReadWrite)
	FText middle_description;

	UPROPERTY(BlueprintReadWrite)
	FText back_description;

	UPROPERTY(BlueprintReadWrite)
	FText order_description;
};
