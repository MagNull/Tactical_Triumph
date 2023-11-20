#include "PlayerTestComponent.h"
#include "AbilitySystemGlobals.h"

UPlayerTestComponent::UPlayerTestComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPlayerTestComponent::BeginPlay()
{
	Super::BeginPlay();
	UAbilitySystemGlobals::Get().InitGlobalData();
}


// Called every frame
void UPlayerTestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

