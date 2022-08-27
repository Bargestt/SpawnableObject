// Copyright (C) Vasily Bulgakov. 2022. All Rights Reserved.

#include "SpawnableObject.h"

DEFINE_LOG_CATEGORY(LogSpawnableObject);

#define LOCTEXT_NAMESPACE "FSpawnableObjectModule"

class FSpawnableObjectModule : public ISpawnableObjectModule
{
public:

	virtual void StartupModule() override
	{

	}
	virtual void ShutdownModule() override
	{

	}
};

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSpawnableObjectModule, SpawnableObject)