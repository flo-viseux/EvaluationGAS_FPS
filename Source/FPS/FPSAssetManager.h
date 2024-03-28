// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "FPSAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UFPSAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	virtual void StartInitialLoading() override;
};
