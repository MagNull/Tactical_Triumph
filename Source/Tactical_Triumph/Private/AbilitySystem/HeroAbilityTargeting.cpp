// Fill out your copyright notice in the Description page of Project Settings.


#include "Tactical_Triumph/Public/AbilitySystem/HeroAbilityTargeting.h"

#include "AbilitySystem/Hero.h"
#include "Kismet/GameplayStatics.h"


FHitResult AHeroAbilityTargeting::PerformTrace(AActor* InSourceActor)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	check(PC);

	FHitResult ReturnHitResult;
	ECollisionChannel CollisionChannel;
	FCollisionResponseParams Params;
	UCollisionProfile::GetChannelAndResponseParams(TraceProfile.Name, CollisionChannel, Params);
	PC->GetHitResultUnderCursor(CollisionChannel, false, ReturnHitResult);

	AHero* TargetHero = Cast<AHero>(ReturnHitResult.GetActor());
	if(TargetHero)
	{
		LastTargetHero = TargetHero;
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
	Super::ConfirmTargeting();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bEnableClickEvents = true;
}

void AHeroAbilityTargeting::CancelTargeting()
{
	Super::CancelTargeting();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bEnableClickEvents = true;
}

FGameplayAbilityTargetDataHandle AHeroAbilityTargeting::MakeTargetData(FHitResult hitResult)
{
	TArray<TWeakObjectPtr<AActor>> TargetActors{};
	if(LastTargetHero == hitResult.GetActor())
	{
		TargetActors.Add(LastTargetHero);
	}
	
	return StartLocation.MakeTargetDataHandleFromActors(TargetActors, true);
}
