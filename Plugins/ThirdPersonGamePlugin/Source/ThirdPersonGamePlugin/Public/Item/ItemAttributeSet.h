// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Macro/AttributeMacros.h"
#include "ItemAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONGAMEPLUGIN_API UItemAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemAttribute")
	FGameplayAttributeData currentItemHp = 100.f;
	ATTRIBUTE_ACCESSORS(UItemAttributeSet, currentItemHp);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemAttribute")
	FGameplayAttributeData itemMaxHealth = 100.f;
	ATTRIBUTE_ACCESSORS(UItemAttributeSet, itemMaxHealth);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemAttribute")
	FString itemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemAttribute")
	float interactionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemAttribute")
	UTexture2D* itemIcon;
};
