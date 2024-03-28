// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

#include "CharacterAttributeSetBase.h"
#include "AbilitySystemComponent.h"
#include "FPS_AbilitySystemComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UFPS_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSetBase = CreateDefaultSubobject<UCharacterAttributeSetBase>(TEXT("AttributeSetBase"));
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	AbilitySystemComponent->BP_ApplyGameplayEffectToSelf(InitStatsEffect, 1, AbilitySystemComponent->MakeEffectContext());
}


UAbilitySystemComponent* AMyActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMyActor::Hit(TSubclassOf<UGameplayAbility> newAbility)
{
	if (!IsValid(newAbility))
		return;

	// if current ability is null, give and activate new ability
	if (CurrentAbility == nullptr)
	{
		CurrentAbility = TSubclassOf<UGameplayAbility>(newAbility);

		AbilitySystemComponent->GiveAbility(CurrentAbility);
		AbilitySystemComponent->TryActivateAbilityByClass(CurrentAbility);
	}
	// if current ability != new ability, clear current abilty, give and activate new ability
	else if (CurrentAbility != nullptr && CurrentAbility != TSubclassOf<UGameplayAbility>(newAbility))
	{
		const FGameplayAbilitySpec* OldFoundAbilitySpec = AbilitySystemComponent->FindAbilitySpecFromClass(CurrentAbility);

		// Clear Current Ability
		if (OldFoundAbilitySpec)
		{
			FGameplayAbilitySpecHandle AbilitySpecHandle;
			AbilitySpecHandle = OldFoundAbilitySpec->Handle;
			AbilitySystemComponent->ClearAbility(AbilitySpecHandle);
		}
		
		// Give and activate new ability
		CurrentAbility = TSubclassOf<UGameplayAbility>(newAbility);

		AbilitySystemComponent->GiveAbility(CurrentAbility);
		AbilitySystemComponent->TryActivateAbilityByClass(CurrentAbility);
	}
	// if current ability == new ability, activate it
	else
	{
		AbilitySystemComponent->TryActivateAbilityByClass(CurrentAbility);
	}

	FString OutputString = FString::Printf(TEXT("HP : %f / %f"), GetHealth(), GetMaxHealth());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, OutputString);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::SetHealth(float Health)
{
	if (IsValid(AttributeSetBase))
		AttributeSetBase->SetHealth(Health);
}

float AMyActor::GetHealth() const
{
	if (IsValid(AttributeSetBase))
		return AttributeSetBase->GetHealth();
	
	return 0.0f;
}

void AMyActor::SetMaxHealth(float MaxHealth)
{
	if (IsValid(AttributeSetBase))
		AttributeSetBase->SetHealth(MaxHealth);
}

float AMyActor::GetMaxHealth() const
{
	if (IsValid(AttributeSetBase))
		return AttributeSetBase->GetMaxHealth();
	
	return 0.0f;
}


