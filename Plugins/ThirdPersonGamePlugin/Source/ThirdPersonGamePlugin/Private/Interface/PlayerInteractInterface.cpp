// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/PlayerInteractInterface.h"
#include "Item/PickableItemClass.h"

// Add default functionality here for any IPlayerInteractInterface functions that are not pure virtual.

bool IPlayerInteractInterface::IsInteractableWithinPlayerFov(AActor* item)
{
	return false;
}

AActor* IPlayerInteractInterface::RemoveInteractableFromPlayerRange(AActor* item)
{
	return nullptr;
}

void IPlayerInteractInterface::InteractWithInteractable(IInteractable* item)
{

}

TArray<IInteractable*> IPlayerInteractInterface::GetAllInteractableInPlayerFovInArray()
{
	return TArray<IInteractable*>();
}
