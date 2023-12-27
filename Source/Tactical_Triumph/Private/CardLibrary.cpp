#include "CardLibrary.h"

#include "AbilitySystem/HeroData.h"
#include "Engine/ObjectLibrary.h"

ACardLibrary::ACardLibrary()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Вернуть первых плееров в столбце != nullptr

TArray<UHeroData*> ACardLibrary::LoadCards()
{
	UObjectLibrary* CardLibrary = UObjectLibrary::CreateLibrary(UHeroData::StaticClass(), false, true);
	CardLibrary->AddToRoot();
	CardLibrary->LoadAssetDataFromPath(FolderPathToAssets);
	CardLibrary->LoadAssetsFromAssetData();

	TArray<UHeroData*> Cards;
	CardLibrary->GetObjects(Cards);
	UE_LOG(LogTemp, Warning, TEXT("Card size: %d"), Cards.Num());

	return Cards;
}
