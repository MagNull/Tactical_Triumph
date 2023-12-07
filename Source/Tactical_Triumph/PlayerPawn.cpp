// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Handle.h"
#include "Squad.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	handle_ = CreateDefaultSubobject<UHandle>(TEXT("Test handle"));
	Squad = CreateDefaultSubobject<USquad>(TEXT("Test squad"));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

TArray<UDA_Card*> APlayerPawn::GetCards() const
{
	return handle_->cards;
}
