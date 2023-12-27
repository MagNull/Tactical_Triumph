#include "Pawn/PlayerPawn.h"

#include "AbilitySystemGlobals.h"
#include "AbilitySystem/PlayerAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Squad/SquadComponent.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);

	Attributes = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("Attributes"));
}

void APlayerPawn::BeginPlay()
{
	UAbilitySystemGlobals::Get().InitGlobalData();
    	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
}

void APlayerPawn::HandleActionPointsChanged()
{
	OnActionPointsChanged(Attributes->GetActionPoints());
}

