#include "Pawn/HandleComponent.h"

UHandleComponent::UHandleComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHandleComponent::AddCard(UHeroData* NewCard)
{
	if(NewCard == nullptr)
	{
		return;
	}

	Cards.Add(NewCard);
}

void UHandleComponent::RemoveCard(UHeroData* CardToRemove)
{
	if(CardToRemove == nullptr)
	{
		return;
	}
	Cards.Remove(CardToRemove);
}

TArray<UHeroData*> UHandleComponent::GetCards()
{
	return Cards;
}

