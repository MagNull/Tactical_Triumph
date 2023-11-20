// Fill out your copyright notice in the Description page of Project Settings.


#include "GASHeroAttributeSetTest.h"

#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UGASHeroAttributeSetTest::UGASHeroAttributeSetTest()
{
	
}

void UGASHeroAttributeSetTest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGASHeroAttributeSetTest, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASHeroAttributeSetTest, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASHeroAttributeSetTest, Attack, COND_None, REPNOTIFY_Always);
}

void UGASHeroAttributeSetTest::OnRep_Health(const FGameplayAttributeData oldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASHeroAttributeSetTest, Health, oldData);
}

void UGASHeroAttributeSetTest::OnRep_MaxHealth(const FGameplayAttributeData oldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASHeroAttributeSetTest, MaxHealth, oldData);
}

void UGASHeroAttributeSetTest::OnRep_Attack(const FGameplayAttributeData oldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASHeroAttributeSetTest, Attack, oldData);
}


