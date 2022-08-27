// Copyright (C) Vasily Bulgakov. 2022. All Rights Reserved.

#include "ActorFactorySpawnSelector.h"
#include "SpawnSelectorInterface.h"
#include "SpawnedByObjectInterface.h"
#include "SpawnableObjectDeveloperSettings.h"

#include <LevelEditorViewport.h>


UActorFactorySpawnSelector::UActorFactorySpawnSelector()
{
	bShowInEditorQuickMenu = false;
	DisplayName = NSLOCTEXT("ASpawnSelectorActorFactory", "DisplayName", "SpawnSelector");
	NewActorClass = AActor::StaticClass();

	USpawnableObjectDeveloperSettings* Settings = GetMutableDefault<USpawnableObjectDeveloperSettings>();
	Settings->OnSettingChanged().AddUObject(this, &UActorFactorySpawnSelector::OnSettingsChanged);

	FPropertyChangedEvent Event(nullptr);
	OnSettingsChanged(Settings, Event);
}

bool UActorFactorySpawnSelector::CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg)
{	
	UObject* Asset = AssetData.GetAsset();
	if (Asset)
	{		
		for (UObject* Selector : Selectors)
		{
			if (Selector)
			{
				TSubclassOf<AActor> ClassToSpawn = ISpawnSelectorInterface::Execute_GetActorToSpawn(Selector, Asset);
				if (ClassToSpawn)
				{
					return true;
				}
			}			
		}
	}		

	return false;
}

AActor* UActorFactorySpawnSelector::SpawnActor(UObject* InAsset, ULevel* InLevel, const FTransform& InTransform, const FActorSpawnParameters& InSpawnParams)
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
			SpawnParamsCopy.bDeferConstruction = true;
			SpawnParamsCopy.Name = InAsset->GetFName();
			SpawnParamsCopy.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;

#if WITH_EDITOR
			SpawnParamsCopy.bTemporaryEditorActor = FLevelEditorViewportClient::IsDroppingPreviewActor();
#endif

			AActor* Actor = LocalLevel->OwningWorld->SpawnActor(DefaultActor->GetClass(), &InTransform, SpawnParamsCopy);
			if (Actor)
			{
				if (Actor->Implements<USpawnedByObjectInterface>())
				{
					ISpawnedByObjectInterface::Execute_SetSpawnedByObject(Actor, InAsset);
				}				

				Actor->FinishSpawning(InTransform);
				return Actor;
			}
		}
	}

	return NULL;
}

UObject* UActorFactorySpawnSelector::GetAssetFromActorInstance(AActor* ActorInstance)
{
	return nullptr;
}

AActor* UActorFactorySpawnSelector::GetDefaultActor(const FAssetData& AssetData)
{
	UObject* Asset = AssetData.GetAsset();
	if (Asset)
	{
		for (UObject* Selector : Selectors)
		{
			if (Selector)
			{
				AActor* DefaultActor = ISpawnSelectorInterface::Execute_GetActorToSpawn(Selector, Asset).GetDefaultObject();
				if (DefaultActor)
				{
					return DefaultActor;
				}
			}
		}
	}

	return nullptr;
}

void UActorFactorySpawnSelector::OnSettingsChanged(UObject* InSettings, struct FPropertyChangedEvent& Event)
{
	const USpawnableObjectDeveloperSettings* Settings = GetDefault<USpawnableObjectDeveloperSettings>();
	if (Settings)
	{
		Selectors.Empty();
		for (const TSoftObjectPtr<UObject>& SelectorPtr : Settings->SpawnSelectors)
		{
			UObject* Selector = SelectorPtr.LoadSynchronous();
			if (Selector)
			{
				Selectors.Add(Selector);
			}
		}
	}	
}

