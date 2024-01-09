#include "Tactical_Triumph/Public/AbilitySystem/HeroAbilityTargeting.h"

#include "BattleState.h"
#include "SelectedTargetsFilter.h"
#include "AbilitySystem/Hero.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/PlayerPawn.h"
#include "Squad/SquadComponent.h"

bool AHeroAbilityTargeting::IsConfirmTargetingAllowed()
{
	FGameplayAbilityTargetDataHandle Handle = MakeTargetData(PerformTrace(SourceActor));
	const bool isAllowed = Handle.Get(0)->GetActors().Num() != 0;
	if(!isAllowed)
	{
		WrongTargetWarning();
	}
	
	return isAllowed;
}

FHitResult AHeroAbilityTargeting::PerformTrace(AActor* InSourceActor)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	check(PC);

	FHitResult ReturnHitResult;
	ECollisionChannel CollisionChannel;
	FCollisionResponseParams RespParams;
	UCollisionProfile::GetChannelAndResponseParams(TraceProfile.Name, CollisionChannel, RespParams);
	PC->GetHitResultUnderCursor(CollisionChannel, false, ReturnHitResult);

	if (!ReturnHitResult.HitObjectHandle.IsValid() || !Filter.FilterPassesForActor(
		ReturnHitResult.HitObjectHandle.FetchActor()))
	{
		return {};
	}

	return ReturnHitResult;
}

bool AHeroAbilityTargeting::ShouldProduceTargetData() const
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	return (PC && PC->IsLocalController()) || ShouldProduceTargetDataOnServer;
}

void AHeroAbilityTargeting::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		bDebug = false;
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(PerformTrace(SourceActor));
		
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}

void AHeroAbilityTargeting::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bEnableClickEvents = false;
}

void AHeroAbilityTargeting::ConfirmTargeting()
{
	FGameplayAbilityTargetDataHandle Handle = MakeTargetData(PerformTrace(SourceActor));
		
	if(Handle.Get(0)->GetActors().Num() == 0)
	{
		WrongTargetWarning();
		return;
	}
	Super::ConfirmTargeting();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bEnableClickEvents = true;
}

void AHeroAbilityTargeting::CancelTargeting()
{
	Super::CancelTargeting();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bEnableClickEvents = true;
}

FGameplayAbilityTargetDataHandle AHeroAbilityTargeting::MakeTargetData(const FHitResult& hitResult) const
{
	TArray<TWeakObjectPtr<AActor>> TargetActors{};
	AActor* TargetActor = hitResult.GetActor();
	AHero* TargetHero = Cast<AHero>(TargetActor);

	switch (SelectionType)
	{
	case ESelectionType::Hero:
		{
			UE_LOG(LogTemp, Display, TEXT("Hero"));

			if (TargetHero)
				TargetActors.Add(TargetActor);
			break;
		}
	case ESelectionType::Column:
		{
			if (!TargetHero)
				break;
			const USquadComponent* Squad = UBattleState::GetActivePlayer()->GetComponentByClass<
				USquadComponent>();
			const ESquadColumn TargetColumn = Squad->GetColumn(TargetHero);
			for (const auto DropZone : Squad->GetDropZonesInColumn(TargetColumn))
			{
				AHero* Hero = DropZone->GetHero();
				if (Hero)
				{
					TargetActors.Add(Hero);
				}
			}
			break;
		}
	case ESelectionType::Row:
		{
			if (!TargetHero)
				break;

			const USquadComponent* Squad = UBattleState::GetActivePlayer()->GetComponentByClass<
				USquadComponent>();
			const ESquadRow TargetRow = Squad->GetRow(TargetHero);
			for (const auto DropZone : Squad->GetDropZonesInRow(TargetRow))
			{
				AHero* Hero = DropZone->GetHero();
				if (Hero)
				{
					TargetActors.Add(Hero);
				}
			}
			break;
		}
	case ESelectionType::Cell:
		{
			ADropZone* Cell = Cast<ADropZone>(TargetActor);
			if (!Cell)
				break;
			TargetActors.Add(Cell);
			break;
		}
	}
	UE_LOG(LogTemp, Display, TEXT("Target Actors num %d"), TargetActors.Num());

	return StartLocation.MakeTargetDataHandleFromActors(TargetActors,
	                                                    SelectionType == ESelectionType::Hero ||
	                                                    SelectionType == ESelectionType::Cell);
}
