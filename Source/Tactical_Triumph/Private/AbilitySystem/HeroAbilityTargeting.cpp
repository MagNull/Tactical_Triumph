// Fill out your copyright notice in the Description page of Project Settings.


#include "Tactical_Triumph/Public/AbilitySystem/HeroAbilityTargeting.h"

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
	
	return ReturnHitResult;
}

bool AHeroAbilityTargeting::ShouldProduceTargetData() const
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	return (PC && PC->IsLocalController()) || ShouldProduceTargetDataOnServer;
}
