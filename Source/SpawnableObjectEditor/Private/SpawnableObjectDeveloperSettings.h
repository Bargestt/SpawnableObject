// Copyright (C) Vasily Bulgakov. 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "SpawnableObjectDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(config = Editor, defaultconfig, meta = (DisplayName = "Spawnable Object"))
class USpawnableObjectDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()	

public:
	/** Allows object spawn from drag. Must implement SpawnSelectorInterface */
	UPROPERTY(EditAnywhere, config, Category = "Spawn from Drag")
	TArray<TSoftObjectPtr<UObject>> SpawnSelectors;	

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
};
