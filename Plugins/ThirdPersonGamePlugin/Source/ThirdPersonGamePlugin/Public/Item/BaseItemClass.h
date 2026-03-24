// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interactable.h"
#include "BaseItemClass.generated.h"

class UItemAttributeSet;
class UAbilitySystemComponent;
class APlayerCharacter;

UCLASS()
class THIRDPERSONGAMEPLUGIN_API ABaseItemClass : public AActor , public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItemClass();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(APlayerCharacter* interactedPlayer) override;

	virtual void UseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	UItemAttributeSet* itemAttribute;

	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;

	void ToggleItemUi(bool toggle);

private:	
	

};
