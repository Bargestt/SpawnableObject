// Copyright (C) Vasily Bulgakov. 2022. All Rights Reserved.


#include "SpawnableObjectDeveloperSettings.h"


void USpawnableObjectDeveloperSettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	SpawnSelectors.RemoveAll([](const TSoftObjectPtr<UObject>& Selector)
	{
		UObject* Obj = Selector.LoadSynchronous();
		return Obj && !Obj->Implements<USpawnSelectorInterface>();
	});

	Super::PostEditChangeProperty(PropertyChangedEvent);
}