// Copyright (C) Vasily Bulgakov. 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpawnedByObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USpawnedByObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Notify object about being spawned using object
 */
class SPAWNABLEOBJECT_API ISpawnedByObjectInterface
{
	GENERATED_BODY()
public:

	/** Fired before construction */
	UFUNCTION(BlueprintNativeEvent, Category = "Spawnable")
	bool SetSpawnedByObject(UObject* Source);
};
