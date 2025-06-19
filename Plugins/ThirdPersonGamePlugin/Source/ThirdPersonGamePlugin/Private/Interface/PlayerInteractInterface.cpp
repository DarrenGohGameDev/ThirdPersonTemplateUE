// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/PlayerInteractInterface.h"
#include "Item/PickableItemClass.h"

// Add default functionality here for any IPlayerInteractInterface functions that are not pure virtual.

bool IPlayerInteractInterface::IsItemWithinPlayerFov(APickableItemClass* item)
{
	return false;
}

APickableItemClass* IPlayerInteractInterface::RemoveItemFromPlayerRange(APickableItemClass* item)
{
	return nullptr;
}

void IPlayerInteractInterface::InteractWithItem(APickableItemClass* item)
{

}

TArray<APickableItemClass*> IPlayerInteractInterface::GetAllItemInPlayerFovInArray()
{
	return TArray<APickableItemClass*>();
}
