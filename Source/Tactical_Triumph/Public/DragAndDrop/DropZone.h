// Fill out your copyright notice in the Description page of Project Settings.

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
	// Sets default values for this actor's properties
	ADropZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AHero* Hero;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
