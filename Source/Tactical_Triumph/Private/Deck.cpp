#include "Deck.h"
#include "CardLibrary.h"
#include "AbilitySystem/HeroData.h"

UDeck::UDeck()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDeck::BeginPlay()
{
	Super::BeginPlay();
	Cards = CardLibrary->LoadCards();
}

int UDeck::GetCount() const
{
	return Cards.Num();
}

UHeroData* UDeck::GetNext()
{
	UE_LOG(LogTemp, Warning, TEXT("Before Card Num"));
	if (Cards.Num() == 0)
	{
		return nullptr;
	}

	UE_LOG(LogTemp, Warning, TEXT("After Card Num"));

	int rand_index = FMath::RandRange(0, Cards.Num() - 1);
	UHeroData* card = Cards[rand_index];
	Cards.RemoveAt(rand_index);
	return card;
}
