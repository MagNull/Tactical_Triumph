#include "Pawn/DeckComponent.h"
#include "CardLibrary.h"
#include "AbilitySystem/HeroData.h"

UDeckComponent::UDeckComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDeckComponent::BeginPlay()
{
	Super::BeginPlay();
	CardsInDeck = CardLibrary->LoadCards();
}

int UDeckComponent::GetCount() const
{
	return CardsInDeck.Num();
}

UHeroData* UDeckComponent::Pop()
{
	if (CardsInDeck.Num() == 0)
	{
		return nullptr;
	}

	int rand_index = FMath::RandRange(0, CardsInDeck.Num() - 1);
	UHeroData* card = CardsInDeck[rand_index];
	CardsInDeck.RemoveAt(rand_index);
	return card;
}
