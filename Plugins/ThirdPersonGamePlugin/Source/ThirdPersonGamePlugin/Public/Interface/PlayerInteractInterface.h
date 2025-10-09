// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface/Interactable.h"
#include "PlayerInteractInterface.generated.h"

class APickableItemClass;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THIRDPERSONGAMEPLUGIN_API IPlayerInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual bool IsInteractableWithinPlayerFov(AActor* item);

	virtual AActor* RemoveInteractableFromPlayerRange(AActor* item);

protected:
	
	virtual void InteractWithInteractable(IInteractable* item);

	virtual TArray<IInteractable*> GetAllInteractableInPlayerFovInArray();
	
	float playerFovRange = 1.f;

	TArray<AActor*> InteractableInPlayerRangeArray;

private:

};
