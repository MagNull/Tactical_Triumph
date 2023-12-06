// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hero/Hero.h"
#include "Tactical_Triumph/AbylitySystem/CastingSystem/RowBenefit.h"
#include "GameFramework/Actor.h"
#include "DropZone.generated.h"

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

	bool IsOccupied;
	AHero* Hero;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	EColumn Column;
	
	UPROPERTY(EditAnywhere)
	ERow Row;
	
	UFUNCTION(BlueprintCallable)
	bool GetIsOccupied();

	UFUNCTION(BlueprintCallable)
	AHero* GetHero();
	
	UFUNCTION(BlueprintCallable)
	void SetHero(AHero* NewHero);
	
};
