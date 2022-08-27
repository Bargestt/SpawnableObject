// Copyright (C) Vasily Bulgakov. 2022. All Rights Reserved.

#include "ActorFactorySpawnableObject.h"
#include "SpawnableObjectInterface.h"
#include <LevelEditorViewport.h>
#include "SpawnableObjectFunctionLibrary.h"


UActorFactorySpawnableObject::UActorFactorySpawnableObject()
{
	DisplayName = NSLOCTEXT("ASpawnableObjectActorFactory", "DisplayName", "SpawnableObject");
	NewActorClass = AActor::StaticClass();
}

bool UActorFactorySpawnableObject::CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg)
{
	UClass* AssetClass = AssetData.GetClass();
	if (!AssetClass || !AssetClass->ImplementsInterface(USpawnableObjectInterface::StaticClass()))
	{
		OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoSpawnableObjectAsset", "Asset must implement SpawnableObjectInterface");
		return false;
	}	

	return true;
}

AActor* UActorFactorySpawnableObject::SpawnActor(UObject* InAsset, ULevel* InLevel, const FTransform& InTransform, const FActorSpawnParameters& InSpawnParams)
{
	if (InAsset)
	{
		ULevel* LocalLevel = ValidateSpawnActorLevel(InLevel, InSpawnParams);

		AActor* DefaultActor = GetDefaultActor(FAssetData(InAsset));
		if ((DefaultActor != nullptr) && (LocalLevel != nullptr))
		{
			FActorSpawnParameters SpawnParamsCopy(InSpawnParams);
			SpawnParamsCopy.OverrideLevel = LocalLevel;
			SpawnParamsCopy.bCreateActorPackage = true;
#if WITH_EDITOR
			SpawnParamsCopy.bTemporaryEditorActor = FLevelEditorViewportClient::IsDroppingPreviewActor();
#endif
			return USpawnableObjectFunctionLibrary::SpawnActorUsingSpawnableObjectInterface(
				LocalLevel->OwningWorld,
				InAsset, 
				DefaultActor->GetClass(), 
				InTransform, 
				SpawnParamsCopy
			);
		}
	}

	return NULL;
}

UObject* UActorFactorySpawnableObject::GetAssetFromActorInstance(AActor* ActorInstance)
{
	return nullptr;
}

AActor* UActorFactorySpawnableObject::GetDefaultActor(const FAssetData& AssetData)
{
	UObject* Asset = AssetData.GetAsset();
	if (Asset && Asset->Implements<USpawnableObjectInterface>())
	{
		TSubclassOf<AActor> Class = ISpawnableObjectInterface::Execute_GetSpawnClass(Asset, nullptr);
		return Class ? Class->GetDefaultObject<AActor>() : nullptr;
	}

	return nullptr;
}

