// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "FPSCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "MyActor.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}


void UTP_WeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

	// Configurez les paramètres de trace
	FCollisionQueryParams TraceParams(FName(TEXT("LineTrace")), false, GetOwner());

	const FRotator Rotation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation();
	const FVector C_Position = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
	
	// Obtenez un point de départ et une direction pour le rayon
	const FVector StartLocation = C_Position; // + MuzzleOffset;
	const FVector EndLocation = StartLocation + Rotation.Vector() * 10000.0f; // 10000.0f is ray dist

	// Résultat de la trace
	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, TraceParams))
	{
		// Un objet a été touché
		AMyActor* HitActor = Cast<AMyActor>(HitResult.GetActor());
		
		if (HitActor != nullptr)
			HitActor->Hit(GameplayAbilty);

		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, .5f);
		DrawDebugPoint(GetWorld(), HitResult.Location, 10.0f, FColor::Green, false, .5f);
	}
}

void UTP_WeaponComponent::AttachWeapon(AFPSCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	// Check that the character is valid, and has no rifle yet
	if (Character == nullptr)
		return;

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetHasRifle(true);

	Character->AddWeapon(this);
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}
}