// Copyright (C) Vasily Bulgakov. 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ActorFactories/ActorFactory.h"
#include "ActorFactorySpawnableObject.generated.h"

/**
 * 
 */
UCLASS()
class SPAWNABLEOBJECTEDITOR_API UActorFactorySpawnableObject : public UActorFactory
{
	GENERATED_BODY()

	UActorFactorySpawnableObject();
	
	// Begin UActorFactory Interface
	virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;
	virtual AActor* SpawnActor(UObject* InAsset, ULevel* InLevel, const FTransform& InTransform, const FActorSpawnParameters& InSpawnParams) override;
	virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;
	AActor* GetDefaultActor(const FAssetData& AssetData) override;
	// End UActorFactory Interface

};
