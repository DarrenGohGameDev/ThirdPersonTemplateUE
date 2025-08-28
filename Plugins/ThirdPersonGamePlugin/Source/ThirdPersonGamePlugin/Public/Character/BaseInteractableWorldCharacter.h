// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Interface/Interactable.h"
#include "BaseInteractableWorldCharacter.generated.h"


class USphereComponent;
/**
 * 
 */
UCLASS()
class THIRDPERSONGAMEPLUGIN_API ABaseInteractableWorldCharacter : public ABaseCharacter, public IInteractable
{
	GENERATED_BODY()
	
public :

	ABaseInteractableWorldCharacter();

protected :

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "InteractDetection")
	USphereComponent* interactDetectionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InteractDetection")
	float interactDetectionRange = 100.f;

	virtual void BeginPlay() override;

	virtual void Interact() override;
};
