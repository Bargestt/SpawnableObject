// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnableObjectFunctionLibrary.h"
#include <GameFramework/Actor.h>
#include "SpawnableObjectInterface.h"
#include "SpawnedByObjectInterface.h"
#include <Engine/Engine.h>


AActor* USpawnableObjectFunctionLibrary::SpawnActorUsingObject(UObject* WorldContextObject, TScriptInterface<ISpawnableObjectInterface> SpawnableObject, const FTransform& Transform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride /*= ESpawnActorCollisionHandlingMethod::Undefined*/, AActor* Owner /*= nullptr*/)
{
	if (SpawnableObject)
	{
		TSubclassOf<AActor> SpawnClass = SpawnableObject->GetSpawnClass(WorldContextObject);
		if (SpawnClass)
		{
			// If the WorldContextObject is a Pawn we will use that as the instigator.
			// Otherwise if the WorldContextObject is an Actor we will share its instigator.
			// If the value is set via the exposed parameter on SpawnNode it will be overwritten anyways, so this is safe to specify here
			UObject* MutableWorldContextObject = const_cast<UObject*>(WorldContextObject);
			APawn* AutoInstigator = Cast<APawn>(MutableWorldContextObject);
			if (AutoInstigator == nullptr)
			{
				if (AActor* ContextActor = Cast<AActor>(MutableWorldContextObject))
				{
					AutoInstigator = ContextActor->GetInstigator();
				}
			}

			FActorSpawnParameters SpawnParams;
			SpawnParams.Instigator = AutoInstigator;
			SpawnParams.SpawnCollisionHandlingOverride = CollisionHandlingOverride;
			SpawnParams.Owner = Owner;

			if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
			{
				return USpawnableObjectFunctionLibrary::SpawnActorUsingSpawnableObjectInterface(World, SpawnableObject.GetObject(), SpawnClass, Transform, SpawnParams);
			}			
		}
	}
	else
	{
		UE_LOG(LogScript, Warning, TEXT("USpawnableObjectFunctionLibrary::SpawnActorUsingObject: can not spawn an actor from an invalid object"));
	}

	return nullptr;
}

AActor* USpawnableObjectFunctionLibrary::SpawnActorUsingSpawnableObjectInterface(UWorld* World, UObject* SpawnableObject, UClass* SelectedClass, const FTransform& Transform, FActorSpawnParameters SpawnParams)
{
	SpawnParams.bDeferConstruction = true;

	AActor* Actor = World->SpawnActor(SelectedClass, &Transform, SpawnParams);
	if (Actor)
	{
		if (Actor->Implements<USpawnedByObjectInterface>())
		{
			ISpawnedByObjectInterface::Execute_SetSpawnedByObject(Actor, SpawnableObject);
		}
		
		ISpawnableObjectInterface::Execute_SpawnableObject_Construct(SpawnableObject, Actor);

		Actor->FinishSpawning(Transform);
	}

	return Actor;
}
