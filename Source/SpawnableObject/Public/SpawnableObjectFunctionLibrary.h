// Copyright (C) Vasily Bulgakov. 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <Engine/World.h>
#include "SpawnableObjectFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SPAWNABLEOBJECT_API USpawnableObjectFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	
	UFUNCTION(BlueprintCallable, Category = "Spawning", meta = (WorldContext = WorldContextObject))
	static AActor* SpawnActorUsingObject(UObject* WorldContextObject, TScriptInterface<ISpawnableObjectInterface> SpawnableObject, const FTransform& Transform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined, AActor* Owner = nullptr);
	


	static AActor* SpawnActorUsingSpawnableObjectInterface(UWorld* World, UObject* SpawnableObject, UClass* SelectedClass, const FTransform& Transform, FActorSpawnParameters SpawnParams);
};
