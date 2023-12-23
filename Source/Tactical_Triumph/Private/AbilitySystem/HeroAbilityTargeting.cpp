// Fill out your copyright notice in the Description page of Project Settings.


#include "Tactical_Triumph/Public/AbilitySystem/HeroAbilityTargeting.h"

#include "AbilitySystem/Hero.h"
#include "Kismet/GameplayStatics.h"
#include "Squad/ISquad.h"
#include "Squad/Squad.h"


FHitResult AHeroAbilityTargeting::PerformTrace(AActor* InSourceActor)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	check(PC);

	FHitResult ReturnHitResult;
	ECollisionChannel CollisionChannel;
	FCollisionResponseParams Params;
	UCollisionProfile::GetChannelAndResponseParams(TraceProfile.Name, CollisionChannel, Params);
	PC->GetHitResultUnderCursor(CollisionChannel, false, ReturnHitResult);

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
	AHero* TargetHero = Cast<AHero>(hitResult.GetActor());
	if (TargetHero == nullptr)
	{
		return StartLocation.MakeTargetDataHandleFromActors(TargetActors, true);
	}

	switch (SelectionType)
	{
	case ESelectionType::Hero:
		{
			TargetActors.Add(hitResult.GetActor());
			break;
		}
	case ESelectionType::Column:
		{
			const ISquad* Squad = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetComponentByClass<USquad>();
			const ESquadColumn TargetColumn = Squad->GetColumn(TargetHero);
			for (const auto Hero : Squad->GetHeroesInColumn(TargetColumn))
			{
				TargetActors.Add(Hero);
			}
			break;
		}
	case ESelectionType::Row:
		{
			const ISquad* Squad = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetComponentByClass<USquad>();
			const ESquadRow TargetRow = Squad->GetRow(TargetHero);
			for (const auto Hero : Squad->GetHeroesInRow(TargetRow))
			{
				TargetActors.Add(Hero);
			}
			break;
		}
	}

	return StartLocation.MakeTargetDataHandleFromActors(TargetActors,
	                                                    SelectionType == ESelectionType::Hero);
}
