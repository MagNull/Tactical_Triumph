#include "Tactical_Triumph/Public/AbilitySystem/PlayerComponent.h"
#include "AbilitySystemGlobals.h"
#include "Kismet/GameplayStatics.h"

UPlayerComponent::UPlayerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPlayerComponent::BeginPlay()
{
	Super::BeginPlay();
	UAbilitySystemGlobals::Get().InitGlobalData();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
}


// Called every frame
void UPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

