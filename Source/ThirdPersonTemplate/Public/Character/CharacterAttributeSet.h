// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Macro/AttributeMacros.h"
#include "CharacterAttributeSet.generated.h"

UCLASS()
class THIRDPERSONTEMPLATE_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public :

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData currentHealth = 100.f;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, currentHealth);

protected :

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData maxHealth = 100.f;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, maxHealth);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(int32 damage);
};
