#include "GASHeroTest.h"
#include "AbilitySystemComponent.h"

AGASHeroTest::AGASHeroTest()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("GAS Componens"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	AbilitySystemComponent->SetIsReplicated(true);
}

void AGASHeroTest::BeginPlay()
{
	Super::BeginPlay();
}

