// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "CharacterAttributeSetBase.h"
#include "FPS_AbilitySystemComponent.h"
#include "MyActor.generated.h"


UCLASS()
class FPS_API AMyActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UCharacterAttributeSetBase* AttributeSetBase;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> InitStatsEffect;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UFPS_AbilitySystemComponent> AbilitySystemComponent;

	// Getter for AbilitySystemComponent
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void Hit(TSubclassOf<UGameplayAbility> newAbility);

	UFUNCTION(BlueprintCallable, Category = Attributes)
	void SetHealth(float Health);

	UFUNCTION(BlueprintCallable, Category = Attributes)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = Attributes)
	void SetMaxHealth(float MaxHealth);

	UFUNCTION(BlueprintCallable, Category = Attributes)
	float GetMaxHealth() const;

private:
	TSubclassOf<class UGameplayAbility> CurrentAbility;
};
