// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Damage.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UGA_Damage : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void K2_EndAbility() override;

	TSubclassOf<class UGameplayEffect> GE_DamageEffect;
	
private:
	// Detect Hit Pawn
	APawn* DetectAffectedPawn();

	FGameplayEffectSpecHandle MakeDamageEffectSpec();

	void ApplyHealingEffect(APawn* TargetPawn, FGameplayEffectSpecHandle& HealingEffectSpecHandle);
};
