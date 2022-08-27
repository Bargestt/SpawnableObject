// Copyright (C) Vasily Bulgakov. 2022. All Rights Reserved.

#include "SpawnableObjectEditor.h"
#include "ActorFactorySpawnableObject.h"
#include "ActorFactorySpawnSelector.h"




#define LOCTEXT_NAMESPACE "FSpawnableObjectEditorModule"



class FSpawnableObjectEditorModule : public ISpawnableObjectEditorModule
{
	void StartupModule() override
	{		
		GEditor->ActorFactories.Add(NewObject<UActorFactorySpawnableObject>(GetTransientPackage()));
		GEditor->ActorFactories.Add(NewObject<UActorFactorySpawnSelector>(GetTransientPackage()));
	}

	void ShutdownModule() override
	{
		
	}
};


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSpawnableObjectEditorModule, SpawnableObjectEditor)