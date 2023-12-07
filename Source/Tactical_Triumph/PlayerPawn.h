// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DA_Card.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class TACTICAL_TRIUMPH_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
protected:
	
	UPROPERTY()
	class UHandle* handle_;

	UPROPERTY()
	class USquad* Squad;

public:	 
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	TArray<UDA_Card*> GetCards() const;
};
