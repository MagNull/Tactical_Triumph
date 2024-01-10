#include "Pawn/DeckComponent.h"

#include "CardLibrary.h"

UDeckComponent::UDeckComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDeckComponent::BeginPlay()
{
	Super::BeginPlay();
	//CardsInDeck = HeroData;
}

int UDeckComponent::GetCount() const
{
	return CardsInDeck.Num();
}

UHeroData* UDeckComponent::Pop()
{
	if(!isInit)
	{
		isInit = true;
		CardsInDeck = HeroData;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(
									 TEXT("Cards load with %d"), CardsInDeck.Num()));
	}
	if (CardsInDeck.Num() == 0)
	{
		return nullptr;
	}

	int rand_index = FMath::RandRange(0, CardsInDeck.Num() - 1);
	UHeroData* card = CardsInDeck[rand_index];
	CardsInDeck.RemoveAt(rand_index);
	return card;
}
