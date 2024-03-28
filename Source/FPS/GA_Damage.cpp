// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Damage.h"

void UGA_Damage::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	APawn* AffectedPawns = DetectAffectedPawn();
	FGameplayEffectSpecHandle DamageEffectSpecHandle = MakeDamageEffectSpec();

	ApplyHealingEffect(AffectedPawns, DamageEffectSpecHandle);

	K2_EndAbility();
}

void UGA_Damage::K2_EndAbility()
{
	Super::K2_EndAbility();
}

APawn* UGA_Damage::DetectAffectedPawn()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		
		const FRotator Rotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		const FVector Location = PlayerController->PlayerCameraManager->GetCameraLocation();
	
		const FVector StartLocation = Location;
		const FVector EndLocation = StartLocation + Rotation.Vector() * 10000.0f; // 10000.0f is ray dist

		FHitResult HitResult;

		FCollisionQueryParams TraceParams(FName(TEXT("LineTrace")), false);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, TraceParams))
		{
			DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, .5f);
			APawn* HitEnemy = Cast<APawn>(HitResult.GetActor());

			if(IsValid(HitEnemy))
				return HitEnemy;
		}
	}

	return nullptr;
}

FGameplayEffectSpecHandle UGA_Damage::MakeDamageEffectSpec()
{
	FGameplayEffectSpecHandle HealingEffectSpecHandle = MakeOutgoingGameplayEffectSpec(GE_DamageEffect, -1);

	return HealingEffectSpecHandle;
}

void UGA_Damage::ApplyHealingEffect(APawn* TargetPawn, FGameplayEffectSpecHandle& HealingEffectSpecHandle)
{

	//ApplyGameplayEffectSpecToTarget(HealingEffectSpecHandle, GetAbilitySystemComponentFromActorInfo(), this, HealingEffectSpecHandle, TargetPawn);
	//ApplyGameplayEffectSpecToTarget(*HealingEffectSpecHandle.Data.Get(), GetAbilitySystemComponentFromActorInfo(), this, TargetPawn);
}
