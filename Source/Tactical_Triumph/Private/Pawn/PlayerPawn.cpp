#include "Pawn/PlayerPawn.h"

#include "AbilitySystemGlobals.h"
#include "AbilitySystem/PlayerAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/DeckComponent.h"
#include "Squad/SquadComponent.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = false;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);

	Attributes = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("Attributes"));
	Deck = CreateDefaultSubobject<UDeckComponent>(TEXT("Deck"));
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	UAbilitySystemGlobals::Get().InitGlobalData();
    	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
}

void APlayerPawn::HandleActionPointsChanged()
{
	OnActionPointsChanged(Attributes->GetActionPoints());
}

