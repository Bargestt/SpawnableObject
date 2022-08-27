// Copyright (C) Vasily Bulgakov. 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <Templates/SubclassOf.h>
#include "SpawnableObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USpawnableObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Implement to spawn actors by dragging asset to the viewport or using function library
 */
class SPAWNABLEOBJECT_API ISpawnableObjectInterface
{
	GENERATED_BODY()
public:

	/** Return valid class to enable spawn */
	UFUNCTION(BlueprintNativeEvent, Category = "Spawnable")
	TSubclassOf<AActor> GetSpawnClass(UObject* WorldContext) const;

	/** Constructs spawned actor using this object */
	UFUNCTION(BlueprintNativeEvent, Category = "Spawnable")
	void SpawnableObject_Construct(AActor* SpawnedActor) const;

	/** Run object setup when beginning play. Must be called manually by SpawnedActor */
	UFUNCTION(BlueprintNativeEvent, Category = "Spawnable")
	void SpawnableObject_BeginPlay(AActor* SpawnedActor) const;

};
