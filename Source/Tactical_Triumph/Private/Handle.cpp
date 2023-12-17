#include "Handle.h"
#include "DragAndDrop/DA_Card.h"

UHandle::UHandle()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHandle::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Handle Begin Play"));
	LoadCards();
}

void UHandle::LoadCards()
{
	FString folderpath("/Game/Assets/Cards");

	UObjectLibrary* CardLibrary = UObjectLibrary::CreateLibrary(UDA_Card::StaticClass(), false, true);
	CardLibrary->AddToRoot();
	CardLibrary->LoadAssetDataFromPath(folderpath);
	CardLibrary->LoadAssetsFromAssetData();

	CardLibrary->GetObjects(Cards);
	UE_LOG(LogTemp, Warning, TEXT("Card size: %d"), Cards.Num());

	for (UDA_Card* CardAsset : Cards)
	{
		FString DataAssetName = CardAsset->CharacterName;
		UE_LOG(LogTemp, Warning, TEXT("Loaded Data Asset: %s"), *DataAssetName);
	}
}

int UHandle::GetCount() const
{
	return Cards.Num();
}

UDA_Card* UHandle::GetNext()
{
	int rand_index = FMath::RandRange(0, Cards.Num() - 1);
	UDA_Card* card = Cards[rand_index];
	Cards.RemoveAt(rand_index);
	return card;
}
