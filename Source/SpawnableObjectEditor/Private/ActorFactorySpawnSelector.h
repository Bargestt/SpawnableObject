// Copyright (C) Vasily Bulgakov. 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ActorFactories/ActorFactory.h"
#include "ActorFactorySpawnSelector.generated.h"

/**
 * 
 */
UCLASS()
class SPAWNABLEOBJECTEDITOR_API UActorFactorySpawnSelector : public UActorFactory
{
	GENERATED_BODY()

	UActorFactorySpawnSelector();
	
	// Begin UActorFactory Interface
	virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;
	virtual AActor* SpawnActor(UObject* InAsset, ULevel* InLevel, const FTransform& InTransform, const FActorSpawnParameters& InSpawnParams) override;
	virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;
	AActor* GetDefaultActor(const FAssetData& AssetData) override;
	// End UActorFactory Interface

private:
	UPROPERTY()
	TArray<UObject*> Selectors;

	void OnSettingsChanged(UObject* Settings, struct FPropertyChangedEvent& Event);
};
