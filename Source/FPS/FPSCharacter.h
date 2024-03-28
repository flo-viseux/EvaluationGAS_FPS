// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemInterface.h"
#include "CharacterAttributeSetBase.h"
#include "FPS_AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "FPSCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UTP_WeaponComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AFPSCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	
	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* HealAction;
	
public:
	AFPSCharacter();

protected:
	virtual void BeginPlay();

	virtual void PossessedBy(AController* NewController);

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UFPS_AbilitySystemComponent> AbilitySystemComponent;

	
	/** Current weapon */
	UTP_WeaponComponent* weaponComponent;

	/** Setter to set the bool */
    void SetWeaponComponent(UTP_WeaponComponent* WeaponComponent)
    {
    	weaponComponent = WeaponComponent;
    }
	

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();
	

	UFUNCTION(BlueprintCallable, Category = Attributes)
	void SetHealth(float Health);

	UFUNCTION(BlueprintCallable, Category = Attributes)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = Attributes)
	void SetMaxHealth(float MaxHealth);

	UFUNCTION(BlueprintCallable, Category = Attributes)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = Attributes)
	void SetDamage(float Damage);

	UFUNCTION(BlueprintCallable, Category = Attributes)
	float GetDamage() const;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for firing input */
	void Fire();

	/** Called for healing input */
	void Heal();
	
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

protected:
	UPROPERTY()
	UCharacterAttributeSetBase* AttributeSetBase;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Abilities")
	TSubclassOf<class UGameplayAbility> GA_Heal;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> InitStatsEffect;
};

