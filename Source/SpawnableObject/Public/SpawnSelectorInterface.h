// Copyright (C) Vasily Bulgakov. 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpawnSelectorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USpawnSelectorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Implement and add asset to settings. Allows to spawn actor using any asset
 */
class SPAWNABLEOBJECT_API ISpawnSelectorInterface
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintNativeEvent, Category = "Spawnable")
	TSubclassOf<AActor> GetActorToSpawn(UObject* Asset) const;
};
