// Copyright Epic Games, Inc. All Rights Reserved.


#include "FPSPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "FPSCharacter.h"

void AFPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}
}

void AFPSPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	AFPSCharacter* CharacterBase = Cast<AFPSCharacter>(P);
	if (CharacterBase)
	{
		CharacterBase->GetAbilitySystemComponent()->InitAbilityActorInfo(CharacterBase, CharacterBase);
	}
}